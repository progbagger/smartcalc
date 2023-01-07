#include "paymentwidget.h"

#include "ui_paymentwidget.h"

calculator::view::PaymentWidget::PaymentWidget(const QDate& date,
                                               QVBoxLayout* parent_layout,
                                               QPushButton* button,
                                               QWidget* parent)
    : QWidget(parent),
      ui(new Ui::PaymentWidget),
      parent_layout(parent_layout),
      delete_button(button) {
  ui->setupUi(this);
  ui->date_input->setDate(date);
}

calculator::view::PaymentWidget::~PaymentWidget() { delete ui; }

QVBoxLayout* calculator::view::PaymentWidget::GetParentLayout() const {
  return parent_layout;
}

QPushButton* calculator::view::PaymentWidget::GetDeleteButton() const {
  return delete_button;
}

QPushButton* calculator::view::PaymentWidget::GetRemoveButton() const {
  return ui->remove_payment_button;
}

const QDate calculator::view::PaymentWidget::GetDate() const {
  return ui->date_input->date();
}

const double calculator::view::PaymentWidget::GetPayment() const {
  return ui->payment_input->value();
}
