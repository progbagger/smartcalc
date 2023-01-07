#ifndef MODEL_MATH_CALC_H_
#define MODEL_MATH_CALC_H_

#include <string>

#include "tokenizer.h"
#include "tokens.h"
#include "validator.h"

namespace s21 {

namespace model {

class MathCalculator {
 public:
  using token_ptr = const Token*;
  using numbers_type = std::stack<Operator::number_pair>;
  using operators_type = std::stack<const Operator*>;

  MathCalculator() = default;

  explicit MathCalculator(const std::string& expression);
  explicit MathCalculator(std::string&& expression);

  const std::string& GetExpression() const;

  void SetExpression(const std::string& expression);

  double Calculate(double x = NAN) const;
  bool GetStatus() const;

 private:
  Tokenizer tokenizer_;
  Validator validator_;

  void DeleteNumbersInStack(std::stack<Operator::number_pair>& numbers) const;

  bool HandleNumber(numbers_type& numbers, token_ptr token, double x) const;
  bool HandleEmptyStackAndOpeningBracket(operators_type& operators,
                                         token_ptr token) const;
  bool HandleClosingBracket(operators_type& operators, numbers_type& numbers,
                            token_ptr token) const;
  void HandleNonEmptyStack(operators_type& operators, numbers_type& numbers,
                           token_ptr token) const;

  void ApplyRestOperators(operators_type& operators,
                          numbers_type& numbers) const;
};

}  // namespace model

}  // namespace s21

#endif  // MODEL_MATH_CALC_H_