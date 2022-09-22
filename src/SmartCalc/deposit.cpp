#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QMainWindow(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
}

deposit::~deposit() { delete ui; }

void deposit::on_actionCalc_triggered() {
  this->hide();
  emit open_calculator();
}

void deposit::on_actionCredit_triggered() {
  this->hide();
  emit open_credit();
}

void deposit::on_clear_clicked() {
  ui->sum_input->setValue(0.0);
  ui->term_input->setValue(1);
  ui->rate_input->setValue(0.0);
  ui->output_table->clear();
  ui->output_table->setRowCount(0);
  ui->output_table->setColumnCount(0);
}

void deposit::on_calculate_clicked() {
  double sum = ui->sum_input->value();
  double rate = ui->rate_input->value();
  int term = ui->term_input->value();
  QString rate_type = ui->rate_type_input->currentText();
  QString term_type = ui->term_type_input->currentText();

  // Setting up the table
  ui->output_table->setShowGrid(false);

  // Outputing table of monthly payments
  int months_term = term_in_months(term, term_type.toStdString().data());
  ui->output_table->clear();
  ui->output_table->setColumnCount(3);
  ui->output_table->setRowCount(1);

  ui->output_table->setHorizontalHeaderLabels(
      {"Sum at end of month", "Monthly profit", "Total profit in moment"});

  ui->output_table->setVerticalHeaderItem(
      0, new QTableWidgetItem(QString::number(0)));
  ui->output_table->setItem(0, 0,
                            new QTableWidgetItem(QString::number(sum, 'f', 2)));
  ui->output_table->setItem(0, 1,
                            new QTableWidgetItem(QString::number(0.0, 'f', 2)));
  ui->output_table->setItem(0, 2,
                            new QTableWidgetItem(QString::number(0.0, 'f', 2)));

  double total_sum = sum;

  for (int i = 1; i <= months_term; i++) {
    ui->output_table->insertRow(i);
    ui->output_table->setVerticalHeaderItem(
        i, new QTableWidgetItem(QString::number(i)));

    double new_sum = calc_deposit(total_sum, rate,
                                  rate_type.toStdString().data(), i, "Months");
    ui->output_table->setItem(
        i, 0, new QTableWidgetItem(QString::number(new_sum, 'f', 2)));
    ui->output_table->setItem(
        i, 1, new QTableWidgetItem(QString::number(new_sum - sum, 'f', 2)));
    sum = new_sum;
    ui->output_table->setItem(
        i, 2,
        new QTableWidgetItem(QString::number(new_sum - total_sum, 'f', 2)));
  }

  ui->output_table->setColumnWidth(0, ui->output_table->width() / 3 - 10);
  ui->output_table->setColumnWidth(1, ui->output_table->width() / 3 - 10);
  ui->output_table->setColumnWidth(2, ui->output_table->width() / 3 - 10);
}
