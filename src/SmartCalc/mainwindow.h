#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>

#include <QKeyEvent>
#include <QMainWindow>

#include "credit.h"
#include "deposit.h"

extern "C" {
#include "../postfix.h"
}

#define MIN_WIDTH_WITH_HISTORY 878
#define MIN_WIDTH MIN_WIDTH_WITH_HISTORY - 200
#define MIN_WIDTH_WITH_PLOT 1277

#ifdef __APPLE__
#define Y_MOVE_FACTOR 28
#else
#define Y_MOVE_FACTOR 0
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void on_sqrt_clicked();
    void on_left_bracket_clicked();
    void on_rigth_bracket_clicked();
    void on_mod_clicked();
    void on_div_clicked();
    void on_pow_clicked();
    void on_digit_7_clicked();
    void on_digit_8_clicked();
    void on_digit_9_clicked();
    void on_multiply_clicked();
    void on_power_of_10_clicked();
    void on_digit_4_clicked();
    void on_digit_5_clicked();
    void on_digit_6_clicked();
    void on_minus_clicked();
    void on_log10_clicked();
    void on_digit_1_clicked();
    void on_digit_2_clicked();
    void on_digit_3_clicked();
    void on_plus_clicked();
    void on_ln_clicked();
    void on_digit_0_clicked();
    void on_dot_clicked();
    void on_equal_clicked();
    void on_erase_clicked(bool next_sym);
    void on_sin_clicked();
    void on_cos_clicked();
    void on_tan_clicked();
    void on_asin_clicked();
    void on_acos_clicked();
    void on_atan_clicked();
    void on_clear_history_clicked();
    void on_clear_clicked();

    void hide_history();
    void hide_plot();

    void show_history();
    void show_plot();

    void on_x_value_textChanged();
    void on_plot_clicked();
    void on_toggle_history_clicked();
    void on_input_output_textChanged();
    void on_clear_plots_clicked();
    void on_center_clicked();
    void on_x_button_clicked();

    QVector<QPair<double, double>> get_ranges();
    void create_graph(const char *expression, QString &name);

    void on_x_range_textEdited();
    void on_y_range_textEdited();
    void on_actionCredit_triggered();

    void on_actionDeposit_triggered();

    void on_x_clear_clicked();

   public slots:
    void credit_closed();
    void from_credit_opened_deposit();
    void deposit_closed();
    void from_deposit_opened_credit();

   private:
    credit credit_calculator;
    deposit deposit_calculator;
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
};
#endif  // MAINWINDOW_H
