#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include "credit_calc.h"
#include "deposit_calc.h"
#include "math_calc.h"

namespace calculator {

namespace model {

class Model {
 public:
  Model() = default;

  MathCalculator* GetMathCalculator() { return &math_calculator_; }
  CreditCalculator* GetCreditCalculator() { return &credit_calculator_; }
  DepositCalculator* GetDepositCalculator() { return &deposit_calculator_; }

 private:
  MathCalculator math_calculator_;
  CreditCalculator credit_calculator_;
  DepositCalculator deposit_calculator_;
};

}  // namespace model

}  // namespace calculator

#endif  // MODEL_MODEL_H_