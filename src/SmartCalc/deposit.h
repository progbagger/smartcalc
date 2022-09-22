#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QMainWindow>

extern "C" {
#include "../credits.h"
}

namespace Ui {
class deposit;
}

class deposit : public QMainWindow {
    Q_OBJECT

   public:
    explicit deposit(QWidget *parent = nullptr);
    ~deposit();

   signals:
    void open_calculator();
    void open_credit();

   private slots:
    void on_actionCalc_triggered();
    void on_actionCredit_triggered();

    void on_clear_clicked();

    void on_calculate_clicked();

   private:
    Ui::deposit *ui;
};

#endif  // DEPOSIT_H
