#ifndef VIEW_MATH_CALCULATOR_VIEW_H_
#define VIEW_MATH_CALCULATOR_VIEW_H_

#include <QMainWindow>

#include "controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MathCalculator;
}
QT_END_NAMESPACE

namespace s21 {

namespace view {

class MathCalculator : public QMainWindow {
  Q_OBJECT

 public:
  MathCalculator(controller::Controller* controller, QWidget* parent = nullptr);
  ~MathCalculator();

 private slots:
  void on_evaluate_clicked();
  void on_expression_returnPressed();
  void on_clear_clicked();
  void on_backspace_clicked();

  void on_one_clicked();
  void on_two_clicked();
  void on_three_clicked();
  void on_four_clicked();
  void on_five_clicked();
  void on_six_clicked();
  void on_seven_clicked();
  void on_eight_clicked();
  void on_nine_clicked();
  void on_zero_clicked();
  void on_dot_clicked();

  void on_move_cursor_to_the_start_clicked();
  void on_move_cursor_left_clicked();
  void on_move_cursor_right_clicked();
  void on_move_cursor_to_the_end_clicked();

  void on_expression_textChanged();

  void on_sin_clicked();
  void on_cos_clicked();
  void on_tan_clicked();
  void on_ln_clicked();
  void on_log_clicked();
  void on_asin_clicked();
  void on_acos_clicked();
  void on_atan_clicked();
  void on_exp_clicked();
  void on_abs_clicked();
  void on_default_opening_bracket_clicked();
  void on_default_closing_bracket_clicked();
  void on_abs_opening_bracket_clicked();
  void on_abs_closing_bracket_clicked();
  void on_factorial_clicked();
  void on_exponent_clicked();
  void on_x_button_clicked();
  void on_plus_clicked();
  void on_minus_clicked();
  void on_multiply_clicked();
  void on_divide_clicked();
  void on_int_mod_clicked();
  void on_mod_clicked();
  void on_sqrt_clicked();
  void on_create_plot_checkbox_clicked();

  void SetupPlots();

  QVector<double> GetPlotRanges();
  void DrawPlot();

  void SetRanges(const QVector<double>& ranges);
  void SetUserOrDefaultRanges();

  void AddGraphToPlots(const QVector<double>& x, const QVector<double>& y);

  void SetupHistory();
  void LogEvaluation(const QString& expression, double x, double result);

  void on_reset_plot_ranges_clicked();
  void on_center_plot_clicked();
  void on_clear_plot_clicked();
  void on_x_min_valueChanged(double arg1);
  void on_x_max_valueChanged(double arg1);
  void on_y_min_valueChanged(double arg1);

  void on_y_max_valueChanged(double arg1);
  void on_show_legend_clicked();
  void on_clear_history_clicked();

  void InputExpressionFromHistory(QTableWidgetItem* item);

  void on_actionCredit_triggered();
  void on_actionDeposit_triggered();
  void on_random_color_checkbox_stateChanged(int arg1);

  void on_x_input_editingFinished();

  void on_pushButton_clicked();

 signals:
  void OpenCreditCalculator();
  void OpenDepositCalculator();

 private:
  Ui::MathCalculator* ui;
  controller::Controller* controller;

  const QString kErrorMsg = "Evaluation error";
  const QString kXRangeError = "X range invalid";
  const QString kYRangeError = "Y range invalid";

  const QVector<double> kDefaultRanges{-10.0, 10.0, -10.0, 10.0};

  static constexpr int kDefaultPlotDotCount = 10000;
  static constexpr double kDefaultPlotSizeMultiplier = 3;
};

}  // namespace view

}  // namespace s21

#endif  // VIEW_MATH_CALCULATOR_VIEW_H_
