#include "deposit_calculator_view.h"

#include "ui_deposit_calculator_view.h"

calculator::view::DepositCalculator::DepositCalculator(
    controller::Controller* controller, QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::DepositCalculator),
      controller(controller) {
  ui->setupUi(this);
  ui->term_start_input->setDate(QDate::currentDate());
  ui->refills_list->hide();
  ui->withdrawals_list->hide();
}

calculator::view::DepositCalculator::~DepositCalculator() { delete ui; }

void calculator::view::DepositCalculator::
    on_actionMath_and_plots_calculator_triggered() {
  emit OpenMathCalculator();
  hide();
}

void calculator::view::DepositCalculator::
    on_actionCredit_calculator_triggered() {
  emit OpenCreditCalculator();
  hide();
}

void calculator::view::DepositCalculator::AddPayment(QVBoxLayout* layout,
                                                     QPushButton* button) {
  button->setEnabled(true);
  PaymentWidget* widget = new PaymentWidget(
      ui->term_start_input->date().addDays(1), layout, button);
  connect(widget->GetRemoveButton(), &QPushButton::clicked, this,
          &DepositCalculator::RemovePayment);
  layout->addWidget(widget);
  widget->show();
  if (button == ui->clear_withdrawals_button) {
    ui->minimum_input->setEnabled(true);
    ui->minimum_label->setEnabled(true);
  }
}

void calculator::view::DepositCalculator::ClearPayments(QVBoxLayout* layout,
                                                        QPushButton* button) {
  while (!layout->isEmpty()) {
    auto to_delete = layout->itemAt(0)->widget();
    layout->removeWidget(to_delete);
    to_delete->hide();
    delete to_delete;
  }
  button->setDisabled(true);
  if (button == ui->clear_withdrawals_button) {
    ui->minimum_input->setEnabled(false);
    ui->minimum_label->setEnabled(false);
  }
}

void calculator::view::DepositCalculator::RemovePayment() {
  PaymentWidget* sender_widget =
      static_cast<PaymentWidget*>(sender()->parent());
  QVBoxLayout* layout = sender_widget->GetParentLayout();
  layout->removeWidget(
      layout->itemAt(layout->indexOf(sender_widget))->widget());
  sender_widget->hide();
  if (sender_widget->GetParentLayout()->isEmpty()) {
    sender_widget->GetDeleteButton()->setDisabled(true);
    if (sender_widget->GetDeleteButton() == ui->clear_withdrawals_button) {
      ui->minimum_input->setEnabled(false);
      ui->minimum_label->setEnabled(false);
    }
  }
  delete sender_widget;
}

void calculator::view::DepositCalculator::PushRecordsInTable(
    const model::DepositCalculator::return_type& records) {
  ui->result_table->setRowCount(0);
  for (const auto& record : records) {
    ui->result_table->insertRow(ui->result_table->rowCount());
    ui->result_table->setVerticalHeaderItem(
        ui->result_table->rowCount() - 1,
        new QTableWidgetItem(
            QString::number(ui->result_table->rowCount() - 1)));
    QString date_content = QString(record.first.ToString().data());
    ui->result_table->setItem(ui->result_table->rowCount() - 1, 0,
                              new QTableWidgetItem(date_content));
    for (int i = 0; i < record.second.size(); ++i) {
      QString content;
      if (!std::isnan(record.second.at(i)))
        content = QString::number(record.second.at(i), 'f', 2);
      ui->result_table->setItem(ui->result_table->rowCount() - 1, i + 1,
                                new QTableWidgetItem(content));
    }
  }
  ui->result_table->setVerticalHeaderItem(ui->result_table->rowCount() - 1,
                                          new QTableWidgetItem("Summary"));
  ui->result_table->setItem(ui->result_table->rowCount() - 1, 0, nullptr);
}

void calculator::view::DepositCalculator::on_add_refill_button_clicked() {
  AddPayment(ui->refills_widgets, ui->clear_refills_button);
}

void calculator::view::DepositCalculator::on_clear_refills_button_clicked() {
  ClearPayments(ui->refills_widgets, ui->clear_refills_button);
}

void calculator::view::DepositCalculator::on_add_withdrawal_button_clicked() {
  AddPayment(ui->withdrawals_widgets, ui->clear_withdrawals_button);
}

void calculator::view::DepositCalculator::
    on_clear_withdrawals_button_clicked() {
  ClearPayments(ui->withdrawals_widgets, ui->clear_withdrawals_button);
}

void calculator::view::DepositCalculator::on_calculate_button_clicked() {
  model::DepositCalculator::Parameters params;
  params.sum = ui->sum_input->value();
  params.term = ui->term_input->value();
  params.term_type = GetTermType();
  QDate input_date = ui->term_start_input->date();
  params.term_start =
      model::Date(input_date.day(), input_date.month(), input_date.year());
  params.rate = ui->rate_input->value();
  params.rate_type = GetRateType();
  if (ui->minimum_input->isEnabled())
    params.minimum_rest = ui->minimum_input->value();
  else
    params.minimum_rest = 0.0;
  params.periodicity_of_payments = GetPaymentPeriodicity();
  params.capitalization_of_interest =
      ui->rate_capitalization_input->isChecked();
  params.refills = GetPaymentList(true);
  params.withdrawals = GetPaymentList(false);

  model::DepositCalculator::return_type result =
      controller->CalculateDeposit(params);
  PushRecordsInTable(result);
}

calculator::model::DepositCalculator::payment_list
calculator::view::DepositCalculator::GetPaymentList(bool is_refill) {
  calculator::model::DepositCalculator::payment_list result;
  QVBoxLayout* current_layout =
      (is_refill ? ui->refills_widgets : ui->withdrawals_widgets);
  for (int i = 0; i < current_layout->count(); ++i) {
    PaymentWidget* current_widget =
        static_cast<PaymentWidget*>(current_layout->itemAt(i)->widget());
    int current_day = current_widget->GetDate().day();
    int current_month = current_widget->GetDate().month();
    int current_year = current_widget->GetDate().year();
    double current_payment = current_widget->GetPayment();
    if (!is_refill) current_payment = -current_payment;
    result.push_back({model::Date(current_day, current_month, current_year),
                      current_payment});
  }
  return result;
}

calculator::model::TermType calculator::view::DepositCalculator::GetTermType() {
  if (ui->term_type_input->currentIndex() == 0)
    return model::TermType::kDays;
  else if (ui->term_type_input->currentIndex() == 1)
    return model::TermType::kMonths;
  else
    return model::TermType::kYears;
}

calculator::model::RateType calculator::view::DepositCalculator::GetRateType() {
  if (ui->rate_type_input->currentIndex() == 0)
    return model::RateType::kPerMonth;
  else
    return model::RateType::kPerAnnum;
}

calculator::model::DepositCalculator::PeriodicityType
calculator::view::DepositCalculator::GetPaymentPeriodicity() {
  switch (ui->payment_periodicity_input->currentIndex()) {
    case 0:
      return model::DepositCalculator::PeriodicityType::kDaily;
      break;
    case 1:
      return model::DepositCalculator::PeriodicityType::kWeekly;
      break;
    case 2:
      return model::DepositCalculator::PeriodicityType::kMonthly;
      break;
    case 3:
      return model::DepositCalculator::PeriodicityType::kPerQuarter;
      break;
    case 4:
      return model::DepositCalculator::PeriodicityType::kPerHalfOfYear;
      break;
    case 5:
      return model::DepositCalculator::PeriodicityType::kPerYear;
      break;
    default:
      return model::DepositCalculator::PeriodicityType::kAtTheEnd;
      break;
  }
}

void calculator::view::DepositCalculator::on_show_refills_list_clicked(
    bool checked) {
  if (checked) {
    ui->refills_list->show();
    ui->show_refills_list->setText("Show");
  } else {
    ui->refills_list->hide();
    ui->show_refills_list->setText(
        "Show (" + QString::number(ui->refills_widgets->count()) + ")");
  }
}

void calculator::view::DepositCalculator::on_show_withdrawals_list_clicked(
    bool checked) {
  if (checked) {
    ui->withdrawals_list->show();
    ui->show_withdrawals_list->setText("Show");
  } else {
    ui->withdrawals_list->hide();
    ui->show_withdrawals_list->setText(
        "Show (" + QString::number(ui->withdrawals_widgets->count()) + ")");
  }
}
