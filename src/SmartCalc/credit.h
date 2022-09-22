#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

extern "C" {
#include "../credits.h"
}

namespace Ui {
class credit;
}

class credit : public QMainWindow {
    Q_OBJECT

   public:
    explicit credit(QWidget *parent = nullptr);
    ~credit();

   signals:
    void open_calculator();
    void open_deposit();

   private slots:
    void on_actionCalc_triggered();
    void on_actionDeposit_triggered();

    void on_calculate_clicked();
    void on_clear_clicked();

   private:
    Ui::credit *ui;
};

#endif  // CREDIT_H
