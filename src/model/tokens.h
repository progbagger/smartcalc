#ifndef MODEL_TOKENS_H_
#define MODEL_TOKENS_H_

#include <cmath>
#include <map>
#include <stack>
#include <string>
#include <tuple>

namespace calculator {

namespace model {

enum TokenType {
  kNumberType,
  kUnaryOperatorType,
  kBinaryOperatorType,
  kFunctionType,
  kBracketType
};

enum Priority {
  kBracketPriority,
  kPlusPriority,
  kMultiplyPriority,
  kPowPriority,
  kUnaryPriority,
  kFunctionPriority
};

using unary_type = double (*)(double);
using binary_type = double (*)(double, double);
using function_type = unary_type;
using bracket_type = function_type;

class Token {
 public:
  Token() = delete;
  virtual ~Token() = 0;

  explicit Token(const std::string& name, TokenType type);

  TokenType GetType() const;

 protected:
  std::string name_;
  const TokenType type_;
};

inline Token::~Token() {}

class Number : public Token {
 public:
  using base = Token;

  Number() = delete;

  explicit Number(double number, bool is_variable = false);
  explicit Number(const std::string& number, bool is_variable = false);

  bool IsVariable() const;

  double GetValue() const;

 private:
  double value_;
  bool is_variable_;
};

class Operator : public Token {
 public:
  using base = Token;
  using number_pair = std::pair<const Number*, bool>;

  Operator() = delete;
  virtual ~Operator() = default;

  explicit Operator(const std::string& name, Priority priority,
                    bool is_right_assotiated, TokenType type);

  virtual void Apply(std::stack<number_pair>& numbers) const = 0;

  bool IsRightAssotiative() const;
  bool IsLeftAssotiative() const;

  bool operator>=(const Operator& other) const;

 protected:
  bool is_right_associative_;
  Priority priority_;

  bool HandleEmptyStack(std::stack<number_pair>& numbers) const;
};

class UnaryOperator : public Operator {
 public:
  using base = Operator;

  UnaryOperator() = delete;

  explicit UnaryOperator(const std::string& name);

  void Apply(std::stack<number_pair>& numbers) const override;

  bool IsPostfix() const;
  bool IsPrefix() const;

  const static std::map<std::string, std::pair<unary_type, bool>> operations_;

 private:
  bool is_postfix_;
};

class BinaryOperator : public Operator {
 public:
  using base = Operator;

  BinaryOperator() = delete;

  explicit BinaryOperator(const std::string& name);

  void Apply(std::stack<number_pair>& numbers) const override;

  const static std::map<std::string, std::tuple<Priority, binary_type, bool>>
      operations_;
};

class Function : public Operator {
 public:
  using base = Operator;

  Function() = delete;

  explicit Function(const std::string& name);

  void Apply(std::stack<number_pair>& numbers) const override;

  const static std::map<std::string, function_type> operations_;
};

class Bracket : public Operator {
 public:
  using base = Operator;

  Bracket() = delete;

  explicit Bracket(const std::string& name);

  void Apply(std::stack<number_pair>& numbers) const override;

  bool IsClosing() const;
  bool IsOpening() const;

  std::size_t GetId() const;

  const static std::map<std::string,
                        std::tuple<bracket_type, bool, std::size_t>>
      operations_;

 private:
  bool is_closing_;
  std::size_t id_;
};

}  // namespace model

}  // namespace calculator

#endif  // MODEL_TOKENS_H_