#include "tokenizer.h"

s21::model::Tokenizer::~Tokenizer() { RemoveData(); }

s21::model::Tokenizer& s21::model::Tokenizer::operator=(
    Tokenizer&& other) noexcept {
  if (this != &other) {
    RemoveData();
    tokens_ = std::move(other.tokens_);
    expression_ = std::move(other.expression_);
    other.tokens_.clear();
  }
  return *this;
}

void s21::model::Tokenizer::RemoveData() {
  for (const auto& i : tokens_) delete i;
}

s21::model::Tokenizer::Tokenizer(const std::string& expression)
    : expression_(expression), tokens_(), is_parced_(false) {
  TokenizeExpression();
}

const std::string& s21::model::Tokenizer::GetExpression() const {
  return expression_;
}

const s21::model::Tokenizer::tokens_type& s21::model::Tokenizer::GetTokensList()
    const {
  return tokens_;
}

bool s21::model::Tokenizer::GetStatus() const { return is_parced_; }

const s21::model::Number* s21::model::Tokenizer::CastToNumber(token_ptr token) {
  return static_cast<const Number*>(token);
}

const s21::model::Operator* s21::model::Tokenizer::CastToOperator(
    token_ptr token) {
  return static_cast<const Operator*>(token);
}

const s21::model::UnaryOperator* s21::model::Tokenizer::CastToUnaryOperator(
    token_ptr token) {
  return static_cast<const UnaryOperator*>(token);
}

const s21::model::Bracket* s21::model::Tokenizer::CastToBracket(
    token_ptr token) {
  return static_cast<const Bracket*>(token);
}

bool s21::model::Tokenizer::IsNumber(token_ptr token) {
  return token && token->GetType() == TokenType::kNumberType;
}

bool s21::model::Tokenizer::IsUnaryOperator(token_ptr token) {
  return token->GetType() == TokenType::kUnaryOperatorType;
}

bool s21::model::Tokenizer::IsBinaryOperator(token_ptr token) {
  return token && token->GetType() == TokenType::kBinaryOperatorType;
}

bool s21::model::Tokenizer::IsFunction(token_ptr token) {
  return token && token->GetType() == TokenType::kFunctionType;
}

bool s21::model::Tokenizer::IsBracket(token_ptr token) {
  return token && token->GetType() == TokenType::kBracketType;
}

bool s21::model::Tokenizer::IsPostfix(token_ptr token) {
  return token && IsUnaryOperator(token) &&
         CastToUnaryOperator(token)->IsPostfix();
}

bool s21::model::Tokenizer::IsPrefix(token_ptr token) {
  return token && IsUnaryOperator(token) &&
         CastToUnaryOperator(token)->IsPrefix();
}

bool s21::model::Tokenizer::IsLeftAssotiative(token_ptr token) {
  return token && IsUnaryOperator(token) &&
         CastToUnaryOperator(token)->IsLeftAssotiative();
}

bool s21::model::Tokenizer::IsClosingBracket(token_ptr token) {
  return token && IsBracket(token) && CastToBracket(token)->IsClosing();
}

bool s21::model::Tokenizer::IsOpeningBracket(token_ptr token) {
  return token && IsBracket(token) && CastToBracket(token)->IsOpening();
}

bool s21::model::Tokenizer::ExpressionContainsAtPos(const std::string& substr,
                                                    size_type pos) const {
  size_type i_substr = 0;
  while (i_substr < substr.length() && pos < expression_.length()) {
    if (expression_.at(pos++) != substr.at(i_substr++)) return false;
  }
  return true;
}

template <class T>
bool s21::model::Tokenizer::FindAndPushTokens(size_type& current_pos) {
  for (const auto& i : T::operations_) {
    if (ExpressionContainsAtPos(i.first, current_pos)) {
      tokens_.push_back(new T(i.first));
      current_pos += i.first.length();
      return true;
    }
  }
  return false;
}

bool s21::model::Tokenizer::CheckUnary(size_type& current_pos) {
  if (tokens_.empty() && expression_.at(current_pos) == '!') return false;
  return FindAndPushTokens<UnaryOperator>(current_pos);
}

bool s21::model::Tokenizer::CheckBinary(size_type& current_pos) {
  if (tokens_.empty()) return false;
  if (IsBinaryOperator(tokens_.back()) || IsOpeningBracket(tokens_.back()) ||
      IsFunction(tokens_.back())) {
    return false;
  }
  return FindAndPushTokens<BinaryOperator>(current_pos);
}

bool s21::model::Tokenizer::CheckFunctions(size_type& current_pos) {
  if (!tokens_.empty()) {
    if (IsNumber(tokens_.back())) {
      return false;
    }
  }
  return FindAndPushTokens<Function>(current_pos);
}

bool s21::model::Tokenizer::CheckOther(size_type& current_pos) {
  return FindAndPushTokens<Bracket>(current_pos);
}

bool s21::model::Tokenizer::CheckVariable(size_type& current_pos) {
  if (expression_.at(current_pos) == 'x') {
    ++current_pos;
    tokens_.push_back(new Number("x"));
    return true;
  }
  return false;
}

bool s21::model::Tokenizer::CheckNumber(size_type& current_pos) {
  try {
    size_type shift = 0;
    double number = std::stod(expression_.substr(current_pos), &shift);
    current_pos += shift;
    tokens_.push_back(new Number(number));
  } catch (...) {
    return false;
  }
  return true;
}

void s21::model::Tokenizer::TokenizeExpression() {
  size_type current_pos = 0;
  while (current_pos < expression_.length()) {
    if (CheckOther(current_pos)) continue;
    if (CheckBinary(current_pos)) continue;
    if (CheckUnary(current_pos)) continue;
    if (CheckFunctions(current_pos)) continue;
    if (CheckVariable(current_pos)) continue;
    if (!CheckNumber(current_pos)) break;
  }
  if (current_pos >= expression_.length()) is_parced_ = true;
}