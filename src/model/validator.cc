#include "validator.h"

s21::model::Validator::Validator(tokenizer_type tokenizer)
    : tokenizer_(tokenizer), is_valid_(Validate()) {}

bool s21::model::Validator::GetStatus() const { return is_valid_; }

bool s21::model::Validator::CheckNumber(token_ptr prev_token, token_ptr token) {
  return Tokenizer::IsNumber(token) &&
         (!prev_token ||
          (Tokenizer::IsPrefix(prev_token) &&
           Tokenizer::IsLeftAssotiative(prev_token)) ||
          Tokenizer::IsBinaryOperator(prev_token) ||
          Tokenizer::IsOpeningBracket(prev_token));
}

bool s21::model::Validator::CheckPostfix(token_ptr prev_token,
                                         token_ptr token) {
  return Tokenizer::IsPostfix(token) &&
         (Tokenizer::IsNumber(prev_token) ||
          Tokenizer::IsClosingBracket(prev_token) ||
          Tokenizer::IsPostfix(prev_token));
}

bool s21::model::Validator::CheckUnaryOperator(token_ptr prev_token,
                                               token_ptr token) {
  return Tokenizer::IsUnaryOperator(token) &&
         ((Tokenizer::IsPrefix(token) &&
           (!prev_token || Tokenizer::IsOpeningBracket(prev_token))) ||
          CheckPostfix(prev_token, token));
}

bool s21::model::Validator::CheckBinaryOperator(token_ptr prev_token,
                                                token_ptr token) {
  return Tokenizer::IsBinaryOperator(token) &&
         (Tokenizer::IsPostfix(prev_token) ||
          Tokenizer::IsClosingBracket(prev_token) ||
          Tokenizer::IsNumber(prev_token));
}

bool s21::model::Validator::CheckFunction(token_ptr prev_token,
                                          token_ptr token) {
  return Tokenizer::IsFunction(token) &&
         (!prev_token || Tokenizer::IsPrefix(prev_token) ||
          Tokenizer::IsBinaryOperator(prev_token) ||
          Tokenizer::IsOpeningBracket(prev_token));
}

bool s21::model::Validator::CheckBracket(
    token_ptr prev_token, token_ptr token,
    std::stack<token_ptr>& opened_brackets) {
  return CheckOpenedBrackets(token, opened_brackets) &&
         ((Tokenizer::IsOpeningBracket(token) &&
           ((!prev_token || Tokenizer::IsBinaryOperator(prev_token) ||
             Tokenizer::IsFunction(prev_token) ||
             Tokenizer::IsOpeningBracket(prev_token)) ||
            Tokenizer::IsPrefix(prev_token))) ||
          (Tokenizer::IsClosingBracket(token) &&
           (Tokenizer::IsNumber(prev_token) ||
            Tokenizer::IsPostfix(prev_token) ||
            Tokenizer::IsClosingBracket(prev_token))));
}

bool s21::model::Validator::CheckToken(token_ptr prev_token, token_ptr token,
                                       std::stack<token_ptr>& opened_brackets) {
  return CheckNumber(prev_token, token) ||
         CheckUnaryOperator(prev_token, token) ||
         CheckBinaryOperator(prev_token, token) ||
         CheckFunction(prev_token, token) ||
         CheckBracket(prev_token, token, opened_brackets);
}

bool s21::model::Validator::CheckOpenedBrackets(
    token_ptr token, std::stack<token_ptr>& opened_brackets) {
  if (!Tokenizer::IsBracket(token)) return false;
  if (Tokenizer::IsClosingBracket(token)) {
    if (opened_brackets.empty() ||
        Tokenizer::CastToBracket(token)->GetId() !=
            Tokenizer::CastToBracket(opened_brackets.top())->GetId())
      return false;
    opened_brackets.pop();
  } else {
    opened_brackets.push(token);
  }
  return true;
}

bool s21::model::Validator::CheckLastToken(
    token_ptr prev_token, token_ptr token,
    std::stack<token_ptr>& opened_brackets) {
  return CheckNumber(prev_token, token) || CheckPostfix(prev_token, token) ||
         CheckOpenedBrackets(token, opened_brackets);
}

bool s21::model::Validator::Validate() const {
  if (!tokenizer_->GetStatus()) return false;
  token_ptr previous = nullptr;
  std::stack<token_ptr> opened_brackets;

  for (auto i = tokenizer_->GetTokensList().begin();
       i != tokenizer_->GetTokensList().end(); ++i) {
    auto save = i;
    ++save;
    if (save == tokenizer_->GetTokensList().end()) break;
    if (!CheckToken(previous, *i, opened_brackets)) return false;
    previous = *i;
  }

  return CheckLastToken(previous, tokenizer_->GetTokensList().back(),
                        opened_brackets) &&
         opened_brackets.empty();
}