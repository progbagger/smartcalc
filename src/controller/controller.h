#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "model.h"

namespace calculator {

namespace controller {

class Controller {
 public:
  Controller() = delete;
  Controller(model::Model* model) : model_(model) {}

  void SetExpression(const std::string& expression) {
    model_->GetMathCalculator()->SetExpression(expression);
  }

  const std::string& GetExpression() const {
    return model_->GetMathCalculator()->GetExpression();
  }

  bool CheckValidationStatus() const {
    return model_->GetMathCalculator()->GetStatus();
  }

  double GetResult(double x = NAN) {
    return model_->GetMathCalculator()->Calculate(x);
  }

  double GetResult(const std::string& expression, double x = NAN) {
    model_->GetMathCalculator()->SetExpression(expression);
    return GetResult(x);
  }

  std::vector<model::CreditCalculator::record_type> CalculateCredit(
      const model::CreditCalculator::Parameters& params) {
    return model_->GetCreditCalculator()->Calculate(params);
  }

  std::vector<model::DepositCalculator::record_type> CalculateDeposit(
      const model::DepositCalculator::Parameters& params) {
    return model_->GetDepositCalculator()->Calculate(params);
  }

 private:
  model::Model* model_;
};

}  // namespace controller

}  // namespace calculator

#endif  // CONTROLLER_CONTROLLER_H_
