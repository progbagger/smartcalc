#ifndef MODEL_TOKENIZER_H_
#define MODEL_TOKENIZER_H_

#include <list>
#include <stdexcept>
#include <string>

#include "tokens.h"

namespace s21 {

namespace model {

class Tokenizer {
 public:
  using token_ptr = const Token*;
  using number_ptr = const Number*;
  using operator_ptr = const Operator*;
  using size_type = typename std::string::size_type;
  using tokens_type = std::list<token_ptr>;

  Tokenizer() = default;
  ~Tokenizer();

  Tokenizer& operator=(Tokenizer&& other) noexcept;

  explicit Tokenizer(const std::string& expression);

  const std::string& GetExpression() const;
  const tokens_type& GetTokensList() const;
  bool GetStatus() const;

  static const Number* CastToNumber(token_ptr token);
  static const Operator* CastToOperator(token_ptr token);
  static const UnaryOperator* CastToUnaryOperator(token_ptr token);
  static const Bracket* CastToBracket(token_ptr token);

  static bool IsNumber(token_ptr token);

  static bool IsUnaryOperator(token_ptr token);
  static bool IsBinaryOperator(token_ptr token);
  static bool IsFunction(token_ptr token);
  static bool IsBracket(token_ptr token);

  static bool IsPostfix(token_ptr token);
  static bool IsPrefix(token_ptr token);

  static bool IsLeftAssotiative(token_ptr token);

  static bool IsClosingBracket(token_ptr token);
  static bool IsOpeningBracket(token_ptr token);

 private:
  std::string expression_;
  tokens_type tokens_;
  bool is_parced_;

  void RemoveData();

  void TokenizeExpression();

  bool ExpressionContainsAtPos(const std::string& substr, size_type pos) const;

  bool CheckUnary(size_type& current_pos);
  bool CheckBinary(size_type& current_pos);
  bool CheckFunctions(size_type& current_pos);
  bool CheckOther(size_type& current_pos);
  bool CheckVariable(size_type& current_pos);
  bool CheckNumber(size_type& current_pos);

  template <class T>
  bool FindAndPushTokens(size_type& current_pos);
};

}  // namespace model

}  // namespace s21

#endif  // MODEL_TOKENIZER_H_