#include "paymentwidget.h"

#include "ui_paymentwidget.h"

s21::view::PaymentWidget::PaymentWidget(const QDate& date,
                                        QVBoxLayout* parent_layout,
                                        QPushButton* button, QWidget* parent)
    : QWidget(parent),
      ui(new Ui::PaymentWidget),
      parent_layout(parent_layout),
      delete_button(button) {
  ui->setupUi(this);
  ui->date_input->setDate(date);
}

s21::view::PaymentWidget::~PaymentWidget() { delete ui; }

QVBoxLayout* s21::view::PaymentWidget::GetParentLayout() const {
  return parent_layout;
}

QPushButton* s21::view::PaymentWidget::GetDeleteButton() const {
  return delete_button;
}

QPushButton* s21::view::PaymentWidget::GetRemoveButton() const {
  return ui->remove_payment_button;
}

const QDate s21::view::PaymentWidget::GetDate() const {
  return ui->date_input->date();
}

const double s21::view::PaymentWidget::GetPayment() const {
  return ui->payment_input->value();
}
