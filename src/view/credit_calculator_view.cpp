#include "credit_calculator_view.h"

#include "ui_credit_calculator_view.h"

s21::view::CreditCalculator::CreditCalculator(
    controller::Controller* controller, QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::CreditCalculator),
      controller(controller) {
  ui->setupUi(this);
}

s21::view::CreditCalculator::~CreditCalculator() { delete ui; }

void s21::view::CreditCalculator::
    on_actionMath_and_plots_calculator_triggered() {
  emit OpenMathCalculator();
  hide();
}

void s21::view::CreditCalculator::on_actionDeposit_calculator_triggered() {
  emit OpenDepositCalculator();
  hide();
}

void s21::view::CreditCalculator::on_calculate_button_clicked() {
  model::CreditCalculator::Parameters params;
  params.sum = ui->sum_input->value();
  params.term = ui->term_input->value();
  params.term_type = GetTermType();
  params.rate = ui->rate_input->value();
  params.rate_type = GetRateType();
  params.credit_type = GetCreditType();
  std::vector<model::CreditCalculator::record_type> result =
      controller->CalculateCredit(params);
  PushRecordsInTable(result);
}

s21::model::TermType s21::view::CreditCalculator::GetTermType() {
  if (ui->term_type_input->currentIndex() == 0)
    return model::TermType::kMonths;
  else
    return model::TermType::kYears;
}

s21::model::RateType s21::view::CreditCalculator::GetRateType() {
  if (ui->rate_input_type->currentIndex() == 0)
    return model::RateType::kPerAnnum;
  else
    return model::RateType::kPerMonth;
}

s21::model::CreditCalculator::CreditType
s21::view::CreditCalculator::GetCreditType() {
  if (ui->credit_type_annuity_radio->isChecked())
    return model::CreditCalculator::CreditType::kAnnuity;
  else
    return model::CreditCalculator::CreditType::kDifferentiated;
}

void s21::view::CreditCalculator::PushRecordsInTable(
    const std::vector<model::CreditCalculator::record_type>& records) {
  ui->result_table->setRowCount(0);
  int current_row = 0;
  for (const auto& record : records) {
    ui->result_table->insertRow(current_row);
    for (std::size_t i = 0; i < record.size(); ++i) {
      QString current_value = QString::number(record.at(i), 'f', 2);
      QString content;
      if (!(current_row == records.size() - 1 && i == 3)) {
        content = current_value;
      }
      ui->result_table->setItem(current_row, i, new QTableWidgetItem(content));
    }
    QString last_vertical_header_name;
    if (current_row == records.size() - 1)
      last_vertical_header_name = "Summary";
    else
      last_vertical_header_name = QString::number(current_row);
    ui->result_table->setVerticalHeaderItem(
        current_row, new QTableWidgetItem(last_vertical_header_name));
    ++current_row;
  }
}
