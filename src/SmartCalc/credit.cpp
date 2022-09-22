#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QMainWindow(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}

credit::~credit() { delete ui; }

void credit::on_actionCalc_triggered() {
  this->hide();
  emit open_calculator();
}

void credit::on_actionDeposit_triggered() {
  this->hide();
  emit open_deposit();
}

void credit::on_calculate_clicked() {
  double sum = ui->sum_input->value();
  double rate = ui->rate_input->value();
  int term = ui->term_input->value();
  QString credit_type = ui->type_input->currentText();
  QString rate_type = ui->rate_type_input->currentText();
  QString term_type = ui->term_type_input->currentText();

  // Setting up the table
  ui->output_table->setShowGrid(false);

  // Outputing table of monthly payments
  int months_term = term_in_months(term, term_type.toStdString().data());
  double rate_monthly = rate_in_monthly(rate, rate_type.toStdString().data());
  ui->output_table->clear();
  ui->output_table->setColumnCount(4);
  ui->output_table->setRowCount(1);

  // Calculating annuity payment
  double monthly_payment = 0;
  if (credit_type == "Annuity") {
    monthly_payment = annuity(sum, rate, rate_type.toStdString().data(),
                              months_term, "Months");
  }
  ui->output_table->setHorizontalHeaderLabels(
      {"Monthly payment", "In debt", "In interest", "After payment"});

  ui->output_table->setVerticalHeaderItem(
      0, new QTableWidgetItem(QString::number(0)));
  ui->output_table->setItem(0, 0,
                            new QTableWidgetItem(QString::number(0.0, 'f', 2)));
  ui->output_table->setItem(0, 1,
                            new QTableWidgetItem(QString::number(0.0, 'f', 2)));
  ui->output_table->setItem(0, 2,
                            new QTableWidgetItem(QString::number(0.0, 'f', 2)));
  ui->output_table->setItem(0, 3,
                            new QTableWidgetItem(QString::number(sum, 'f', 2)));

  double total_sum = sum;

  for (int i = 1; i <= months_term; i++) {
    ui->output_table->insertRow(i);
    ui->output_table->setVerticalHeaderItem(
        i, new QTableWidgetItem(QString::number(i)));
    if (credit_type == "Differentiated")
      monthly_payment =
          differentiated(total_sum, sum, rate, rate_type.toStdString().data(),
                         months_term, "Months");
    ui->output_table->setItem(
        i, 0, new QTableWidgetItem(QString::number(monthly_payment, 'f', 2)));

    double in_interest = sum * rate_monthly;

    ui->output_table->setItem(i, 1,
                              new QTableWidgetItem(QString::number(
                                  monthly_payment - in_interest, 'f', 2)));
    ui->output_table->setItem(
        i, 2, new QTableWidgetItem(QString::number(in_interest, 'f', 2)));
    if (credit_type == "Annuity")
      sum -= monthly_payment - in_interest;
    else
      sum -= total_sum / months_term;
    if (fabs(sum) < 1e-6) sum = 0.0;
    ui->output_table->setItem(
        i, 3, new QTableWidgetItem(QString::number(sum, 'f', 2)));
  }

  ui->output_table->setColumnWidth(0, ui->output_table->width() / 4 - 10);
  ui->output_table->setColumnWidth(1, ui->output_table->width() / 4 - 10);
  ui->output_table->setColumnWidth(2, ui->output_table->width() / 4 - 10);
  ui->output_table->setColumnWidth(3, ui->output_table->width() / 4 - 10);
}

void credit::on_clear_clicked() {
  ui->sum_input->setValue(0.0);
  ui->term_input->setValue(1);
  ui->rate_input->setValue(0.0);
  ui->output_table->clear();
  ui->output_table->setRowCount(0);
  ui->output_table->setColumnCount(0);
}
