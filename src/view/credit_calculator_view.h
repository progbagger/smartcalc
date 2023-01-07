#ifndef VIEW_CREDIT_CALCULATOR_VIEW_H_
#define VIEW_CREDIT_CALCULATOR_VIEW_H_

#include <QMainWindow>

#include "controller.h"

namespace Ui {
class CreditCalculator;
}

namespace calculator {

namespace view {

class CreditCalculator : public QMainWindow {
  Q_OBJECT

 public:
  CreditCalculator(controller::Controller *controller,
                   QWidget *parent = nullptr);
  ~CreditCalculator();

 signals:
  void OpenMathCalculator();
  void OpenDepositCalculator();

 private slots:
  void on_actionMath_and_plots_calculator_triggered();
  void on_actionDeposit_calculator_triggered();
  void on_calculate_button_clicked();

 private:
  Ui::CreditCalculator *ui;
  controller::Controller *controller;

  model::TermType GetTermType();
  model::RateType GetRateType();
  model::CreditCalculator::CreditType GetCreditType();

  void PushRecordsInTable(
      const std::vector<model::CreditCalculator::record_type> &records);
};

}  // namespace view

}  // namespace calculator

#endif  // VIEW_CREDIT_CALCULATOR_VIEW_H_
