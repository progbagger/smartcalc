#ifndef MODEL_VALIDATOR_H_
#define MODEL_VALIDATOR_H_

#include "tokenizer.h"

namespace calculator {

namespace model {

class Validator {
 public:
  using token_ptr = const Token*;
  using tokenizer_type = const Tokenizer*;

  Validator() = default;

  explicit Validator(tokenizer_type tokenizer);

  bool GetStatus() const;

 private:
  tokenizer_type tokenizer_;
  bool is_valid_;

  bool Validate() const;

  static bool CheckToken(token_ptr prev_token, token_ptr token,
                         std::stack<token_ptr>& opened_brackets);
  static bool CheckLastToken(token_ptr prev_token, token_ptr token,
                             std::stack<token_ptr>& opened_brackets);

  static bool CheckOpenedBrackets(token_ptr token,
                                  std::stack<token_ptr>& opened_brackets);
  static bool CheckPostfix(token_ptr prev_token, token_ptr token);

  static bool CheckNumber(token_ptr prev_token, token_ptr token);
  static bool CheckUnaryOperator(token_ptr prev_token, token_ptr token);
  static bool CheckBinaryOperator(token_ptr prev_token, token_ptr token);
  static bool CheckFunction(token_ptr prev_token, token_ptr token);
  static bool CheckBracket(token_ptr prev_token, token_ptr token,
                           std::stack<token_ptr>& opened_brackets);
};

}  // namespace model

}  // namespace calculator

#endif  // MODEL_VALIDATOR_H_