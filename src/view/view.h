#ifndef VIEW_VIEW_H
#define VIEW_VIEW_H

#include "controller.h"
#include "credit_calculator_view.h"
#include "deposit_calculator_view.h"
#include "math_calculator_view.h"

namespace calculator {

namespace view {

class View {
 public:
  View() = delete;
  explicit View(controller::Controller* controller)
      : controller(controller),
        math_calculator(new MathCalculator(controller)),
        credit_calculator(new CreditCalculator(controller)),
        deposit_calculator(new DepositCalculator(controller)) {
    SetupConnections();
  }

  ~View() {
    delete math_calculator;
    delete credit_calculator;
    delete deposit_calculator;
  }

  void Start() { math_calculator->show(); }

  void SetupConnections() {
    math_calculator->connect(credit_calculator,
                             &CreditCalculator::OpenMathCalculator,
                             math_calculator, &MathCalculator::show);
    math_calculator->connect(deposit_calculator,
                             &DepositCalculator::OpenMathCalculator,
                             math_calculator, &MathCalculator::show);
    credit_calculator->connect(math_calculator,
                               &MathCalculator::OpenCreditCalculator,
                               credit_calculator, &CreditCalculator::show);
    credit_calculator->connect(deposit_calculator,
                               &DepositCalculator::OpenCreditCalculator,
                               credit_calculator, &CreditCalculator::show);
    deposit_calculator->connect(math_calculator,
                                &MathCalculator::OpenDepositCalculator,
                                deposit_calculator, &DepositCalculator::show);
    deposit_calculator->connect(credit_calculator,
                                &CreditCalculator::OpenDepositCalculator,
                                deposit_calculator, &DepositCalculator::show);
  }

 private:
  controller::Controller* controller;

  MathCalculator* math_calculator;
  CreditCalculator* credit_calculator;
  DepositCalculator* deposit_calculator;
};

}  // namespace view

}  // namespace calculator

#endif  // VIEW_VIEW_H
