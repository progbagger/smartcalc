#include "math_calc.h"

calculator::model::MathCalculator::MathCalculator(const std::string& expression)
    : tokenizer_(expression), validator_(&tokenizer_) {}

calculator::model::MathCalculator::MathCalculator(std::string&& expression)
    : tokenizer_(expression), validator_(&tokenizer_) {}

const std::string& calculator::model::MathCalculator::GetExpression() const {
  return tokenizer_.GetExpression();
}

void calculator::model::MathCalculator::SetExpression(
    const std::string& expression) {
  *this = std::move(MathCalculator(expression));
}

bool calculator::model::MathCalculator::GetStatus() const {
  return validator_.GetStatus();
}

void calculator::model::MathCalculator::DeleteNumbersInStack(
    std::stack<Operator::number_pair>& stack) const {
  while (!stack.empty()) {
    if (stack.top().second) delete stack.top().first;
    stack.pop();
  }
}

bool calculator::model::MathCalculator::HandleNumber(numbers_type& numbers,
                                                     token_ptr token,
                                                     double x) const {
  if (Tokenizer::IsNumber(token)) {
    const Number* number = Tokenizer::CastToNumber(token);
    if (number->IsVariable()) {
      numbers.push({new Number(x, true), true});
    } else {
      numbers.push({number, false});
    }
    return true;
  }
  return false;
}

bool calculator::model::MathCalculator::HandleEmptyStackAndOpeningBracket(
    operators_type& operators, token_ptr token) const {
  if (operators.empty() || Tokenizer::IsOpeningBracket(token)) {
    operators.push(Tokenizer::CastToOperator(token));
    return true;
  }
  return false;
}

bool calculator::model::MathCalculator::HandleClosingBracket(
    operators_type& operators, numbers_type& numbers, token_ptr token) const {
  if (Tokenizer::IsClosingBracket(token)) {
    while (!operators.empty() &&
           !Tokenizer::IsOpeningBracket(operators.top())) {
      operators.top()->Apply(numbers);
      operators.pop();
    }
    operators.pop();
    Tokenizer::CastToOperator(token)->Apply(numbers);
    return true;
  }
  return false;
}

void calculator::model::MathCalculator::HandleNonEmptyStack(
    operators_type& operators, numbers_type& numbers, token_ptr token) const {
  while (!operators.empty() && !Tokenizer::IsOpeningBracket(operators.top()) &&
         *operators.top() >= *Tokenizer::CastToOperator(token)) {
    operators.top()->Apply(numbers);
    operators.pop();
  }
  operators.push(Tokenizer::CastToOperator(token));
}

void calculator::model::MathCalculator::ApplyRestOperators(
    operators_type& operators, numbers_type& numbers) const {
  while (!operators.empty()) {
    operators.top()->Apply(numbers);
    operators.pop();
  }
}

double calculator::model::MathCalculator::Calculate(double x) const {
  if (!GetStatus()) return NAN;
  numbers_type numbers;
  operators_type operators;
  for (const auto& current_token : tokenizer_.GetTokensList()) {
    if (HandleNumber(numbers, current_token, x)) continue;
    if (HandleEmptyStackAndOpeningBracket(operators, current_token)) continue;
    if (HandleClosingBracket(operators, numbers, current_token)) continue;
    HandleNonEmptyStack(operators, numbers, current_token);
  }
  ApplyRestOperators(operators, numbers);
  double result = NAN;
  if (numbers.size() == 1) result = numbers.top().first->GetValue();
  DeleteNumbersInStack(numbers);
  return result;
}