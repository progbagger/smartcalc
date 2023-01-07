#ifndef VIEW_DEPOSIT_CALCULATOR_VIEW_H_
#define VIEW_DEPOSIT_CALCULATOR_VIEW_H_

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>

#include "controller.h"
#include "paymentwidget.h"

namespace Ui {
class DepositCalculator;
}

namespace s21 {

namespace view {

class DepositCalculator : public QMainWindow {
  Q_OBJECT

 public:
  explicit DepositCalculator(controller::Controller *controller,
                             QWidget *parent = nullptr);
  ~DepositCalculator();

 signals:
  void OpenMathCalculator();
  void OpenCreditCalculator();

 private slots:
  void on_actionMath_and_plots_calculator_triggered();
  void on_actionCredit_calculator_triggered();
  void on_add_refill_button_clicked();
  void on_clear_refills_button_clicked();
  void on_add_withdrawal_button_clicked();
  void on_clear_withdrawals_button_clicked();
  void on_calculate_button_clicked();

  void on_show_refills_list_clicked(bool checked);

  void on_show_withdrawals_list_clicked(bool checked);

 private:
  Ui::DepositCalculator *ui;
  controller::Controller *controller;

  model::DepositCalculator::payment_list GetPaymentList(bool is_refill);

  model::TermType GetTermType();
  model::RateType GetRateType();
  model::DepositCalculator::PeriodicityType GetPaymentPeriodicity();

  void AddPayment(QVBoxLayout *layout, QPushButton *button);
  void ClearPayments(QVBoxLayout *layout, QPushButton *button);
  void RemovePayment();

  void PushRecordsInTable(const model::DepositCalculator::return_type &records);
};

}  // namespace view

}  // namespace s21

#endif  // VIEW_DEPOSIT_CALCULATOR_VIEW_H_
