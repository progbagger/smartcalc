#ifndef PAYMENTWIDGET_H
#define PAYMENTWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class PaymentWidget;
}

namespace calculator {

namespace view {

class PaymentWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PaymentWidget(const QDate &date, QVBoxLayout *parent_layout,
                         QPushButton *button, QWidget *parent = nullptr);
  ~PaymentWidget();

  QVBoxLayout *GetParentLayout() const;
  QPushButton *GetDeleteButton() const;
  QPushButton *GetRemoveButton() const;

  const QDate GetDate() const;
  const double GetPayment() const;

 private:
  Ui::PaymentWidget *ui;
  QVBoxLayout *parent_layout;
  QPushButton *delete_button;
};

}  // namespace view

}  // namespace calculator

#endif  // PAYMENTWIDGET_H
