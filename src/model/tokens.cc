#include "tokens.h"

// Lists of valid lexems

// {name, {function, postfix or prefix}}
inline const std::map<std::string,
                      std::pair<calculator::model::unary_type, bool>>
    calculator::model::UnaryOperator::operations_{
        {"-", {[](double num) { return -num; }, false}},
        {"+", {[](double num) { return num; }, false}},
        {"!",
         {[](double num) {
            if (!std::isfinite(num) || num < 0) return (double)NAN;
            double result = 1;
            for (double i = 2; i <= floor(num); ++i) {
              result *= i;
              if (!std::isfinite(result)) break;
            }
            return result;
          },
          true}}};

// {name, {priority, function, assotiativity}}
inline const std::map<std::string,
                      std::tuple<calculator::model::Priority,
                                 calculator::model::binary_type, bool>>
    calculator::model::BinaryOperator::operations_{
        {"+", std::tuple{Priority::kPlusPriority,
                         [](double num1, double num2) { return num1 + num2; },
                         false}},
        {"-", std::tuple{Priority::kPlusPriority,
                         [](double num1, double num2) { return num1 - num2; },
                         false}},
        {"*", std::tuple{Priority::kMultiplyPriority,
                         [](double num1, double num2) { return num1 * num2; },
                         false}},
        {"/", std::tuple{Priority::kMultiplyPriority,
                         [](double num1, double num2) { return num1 / num2; },
                         false}},
        {":", std::tuple{Priority::kMultiplyPriority,
                         [](double num1, double num2) { return num1 / num2; },
                         false}},
        {"div",
         std::tuple{Priority::kMultiplyPriority,
                    [](double num1, double num2) { return floor(num1) / num2; },
                    false}},
        {"%", std::tuple{Priority::kMultiplyPriority,
                         [](double num1, double num2) -> double {
                           long long int_num1 = num1, int_num2 = num2;
                           if (int_num2 == 0) return NAN;
                           return int_num1 % int_num2;
                         },
                         false}},
        {"fmod",
         std::tuple<Priority, binary_type, bool>{Priority::kMultiplyPriority,
                                                 fmod, true}},
        {"mod",
         std::tuple<Priority, binary_type, bool>{
             Priority::kMultiplyPriority, fmod, true}},
        {"^", std::tuple<Priority, binary_type, bool>{Priority::kPowPriority,
                                                      pow, true}},
        {"pow", std::tuple<Priority, binary_type, bool>{Priority::kPowPriority,
                                                        pow, true}}};

// {name, function}
inline const std::map<std::string, calculator::model::function_type>
    calculator::model::Function::operations_{
        {"sin", sin},
        {"cos", cos},
        {"tan", tan},
        {"acos", acos},
        {"asin", asin},
        {"atan", atan},
        {"tg", tan},
        {"ctg", [](double num) { return 1.0 / tan(num); }},
        {"sqrt", sqrt},
        {"log", log10},
        {"ln", log},
        {"exp", exp},
        {"fabs", fabs},
        {"abs", fabs},
        {"fact", std::get<unary_type>(UnaryOperator::operations_.at("!"))}};

// {name, {priority, function, closing or opening, id (make pair brackets with
// one id)}}
inline const std::map<std::string, std::tuple<calculator::model::function_type,
                                              bool, std::size_t>>
    calculator::model::Bracket::operations_{
        {"(", std::tuple{nullptr, false, 0UL}},
        {")", std::tuple{[](double num) { return num; }, true, 0UL}},
        {"[", std::tuple{nullptr, false, 1UL}},
        {"]", std::tuple{Function::operations_.at("fabs"), true, 1UL}}};

// Lists of lexems ended

calculator::model::Token::Token(const std::string& name, TokenType type)
    : name_(name), type_(type) {}

calculator::model::TokenType calculator::model::Token::GetType() const {
  return type_;
}

calculator::model::Number::Number(double number, bool is_variable)
    : base(std::to_string(number), TokenType::kNumberType),
      value_(number),
      is_variable_(is_variable) {}

calculator::model::Number::Number(const std::string& number, bool is_variable)
    : base(number, TokenType::kNumberType) {
  is_variable_ = true;
  value_ = NAN;
}

bool calculator::model::Number::IsVariable() const { return is_variable_; }

double calculator::model::Number::GetValue() const { return value_; }

calculator::model::Operator::Operator(const std::string& name,
                                      Priority priority,
                                      bool is_right_assotiated, TokenType type)
    : base(name, type),
      is_right_associative_(is_right_assotiated),
      priority_(priority) {}

bool calculator::model::Operator::HandleEmptyStack(
    std::stack<number_pair>& numbers) const {
  if (numbers.empty()) {
    numbers.push(std::pair{new Number(NAN), true});
    return true;
  }
  return false;
}

bool calculator::model::Operator::IsRightAssotiative() const {
  return is_right_associative_;
}

bool calculator::model::Operator::IsLeftAssotiative() const {
  return !IsRightAssotiative();
}

bool calculator::model::Operator::operator>=(const Operator& other) const {
  return (priority_ >= other.priority_) ^
         (IsRightAssotiative() && other.IsRightAssotiative());
}

calculator::model::UnaryOperator::UnaryOperator(const std::string& name)
    : base(name, Priority::kUnaryPriority, false,
           TokenType::kUnaryOperatorType),
      is_postfix_(std::get<bool>(operations_.at(name))) {}

void calculator::model::UnaryOperator::Apply(
    std::stack<number_pair>& numbers) const {
  if (HandleEmptyStack(numbers)) return;
  number_pair number = numbers.top();
  numbers.pop();
  numbers.push(std::pair{new Number(std::get<unary_type>(operations_.at(name_))(
                             (number.first->GetValue()))),
                         true});
  if (number.second) delete number.first;
}

bool calculator::model::UnaryOperator::IsPostfix() const { return is_postfix_; }
bool calculator::model::UnaryOperator::IsPrefix() const { return !IsPostfix(); }

calculator::model::BinaryOperator::BinaryOperator(const std::string& name)
    : base(name, std::get<Priority>(operations_.at(name)),
           std::get<bool>(operations_.at(name)),
           TokenType::kBinaryOperatorType) {}

void calculator::model::BinaryOperator::Apply(
    std::stack<number_pair>& numbers) const {
  if (HandleEmptyStack(numbers)) return;
  number_pair number1 = numbers.top();
  numbers.pop();
  if (HandleEmptyStack(numbers)) return;
  number_pair number2 = numbers.top();
  numbers.pop();
  numbers.push(
      std::pair{new Number(std::get<binary_type>(operations_.at(name_))(
                    number2.first->GetValue(), number1.first->GetValue())),
                true});
  if (number1.second) delete number1.first;
  if (number2.second) delete number2.first;
}

calculator::model::Function::Function(const std::string& name)
    : base(name, Priority::kFunctionPriority, false, TokenType::kFunctionType) {
}

void calculator::model::Function::Apply(
    std::stack<number_pair>& numbers) const {
  if (HandleEmptyStack(numbers)) return;
  number_pair number = numbers.top();
  numbers.pop();
  numbers.push(std::pair{
      new Number(operations_.at(name_)(number.first->GetValue())), true});
  if (number.second) delete number.first;
}

calculator::model::Bracket::Bracket(const std::string& name)
    : base(name, Priority::kBracketPriority, false, TokenType::kBracketType),
      is_closing_(std::get<bool>(operations_.at(name))),
      id_(std::get<std::size_t>(operations_.at(name))) {}

void calculator::model::Bracket::Apply(std::stack<number_pair>& numbers) const {
  if (!std::get<bool>(operations_.at(name_))) return;
  if (HandleEmptyStack(numbers)) return;
  number_pair number = numbers.top();
  numbers.pop();
  numbers.push(std::pair{new Number(std::get<bracket_type>(
                             operations_.at(name_))(number.first->GetValue())),
                         true});
  if (number.second) delete number.first;
}

bool calculator::model::Bracket::IsClosing() const { return is_closing_; }
bool calculator::model::Bracket::IsOpening() const { return !IsClosing(); }

std::size_t calculator::model::Bracket::GetId() const { return id_; }