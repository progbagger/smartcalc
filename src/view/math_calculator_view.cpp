#include "math_calculator_view.h"

#include "ui_math_calculator_view.h"

calculator::view::MathCalculator::MathCalculator(
    controller::Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MathCalculator), controller(controller) {
  ui->setupUi(this);
  SetupPlots();
  SetupHistory();
}

calculator::view::MathCalculator::~MathCalculator() { delete ui; }

void calculator::view::MathCalculator::on_evaluate_clicked() {
  if (ui->expression->text().isEmpty()) return;
  controller->SetExpression(
      ui->expression->text().replace(' ', "").toStdString());
  if (controller->CheckValidationStatus()) {
    LogEvaluation(ui->expression->text().replace(' ', ""), ui->x_input->value(),
                  ui->expression->text().toDouble());
    if (ui->create_plot_checkbox->isChecked()) DrawPlot();
    ui->expression->setText(
        QString::number(controller->GetResult(ui->x_input->value()), 'g', 10));
  } else {
    ui->invalid_input_label->setText(kErrorMsg);
  }
}

void calculator::view::MathCalculator::on_expression_returnPressed() {
  on_evaluate_clicked();
}

void calculator::view::MathCalculator::on_clear_clicked() {
  ui->expression->clear();
}

void calculator::view::MathCalculator::on_backspace_clicked() {
  ui->expression->backspace();
}

void calculator::view::MathCalculator::on_one_clicked() {
  ui->expression->insert("1");
}

void calculator::view::MathCalculator::on_two_clicked() {
  ui->expression->insert("2");
}

void calculator::view::MathCalculator::on_three_clicked() {
  ui->expression->insert("3");
}

void calculator::view::MathCalculator::on_four_clicked() {
  ui->expression->insert("4");
}

void calculator::view::MathCalculator::on_five_clicked() {
  ui->expression->insert("5");
}

void calculator::view::MathCalculator::on_six_clicked() {
  ui->expression->insert("6");
}

void calculator::view::MathCalculator::on_seven_clicked() {
  ui->expression->insert("7");
}

void calculator::view::MathCalculator::on_eight_clicked() {
  ui->expression->insert("8");
}

void calculator::view::MathCalculator::on_nine_clicked() {
  ui->expression->insert("9");
}

void calculator::view::MathCalculator::on_zero_clicked() {
  ui->expression->insert("0");
}

void calculator::view::MathCalculator::on_dot_clicked() {
  ui->expression->insert(".");
}

void calculator::view::MathCalculator::on_move_cursor_to_the_start_clicked() {
  ui->expression->setCursorPosition(0);
}

void calculator::view::MathCalculator::on_move_cursor_left_clicked() {
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_move_cursor_right_clicked() {
  ui->expression->cursorForward(false);
}

void calculator::view::MathCalculator::on_move_cursor_to_the_end_clicked() {
  ui->expression->setCursorPosition(ui->expression->text().length());
}

void calculator::view::MathCalculator::on_expression_textChanged() {
  ui->invalid_input_label->clear();
}

void calculator::view::MathCalculator::on_sin_clicked() {
  ui->expression->insert("sin()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_cos_clicked() {
  ui->expression->insert("cos()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_tan_clicked() {
  ui->expression->insert("tan()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_ln_clicked() {
  ui->expression->insert("ln()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_log_clicked() {
  ui->expression->insert("log()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_asin_clicked() {
  ui->expression->insert("asin()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_acos_clicked() {
  ui->expression->insert("acos()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_atan_clicked() {
  ui->expression->insert("atan()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_exp_clicked() {
  ui->expression->insert("exp()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_abs_clicked() {
  ui->expression->insert("abs()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_default_opening_bracket_clicked() {
  ui->expression->insert("()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_default_closing_bracket_clicked() {
  if (ui->expression->text().length() > ui->expression->cursorPosition() &&
      ui->expression->text().at(ui->expression->cursorPosition()) == ')') {
    ui->expression->cursorForward(false);
  } else {
    ui->expression->insert(")");
  }
}

void calculator::view::MathCalculator::on_abs_opening_bracket_clicked() {
  ui->expression->insert("[]");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::on_abs_closing_bracket_clicked() {
  if (ui->expression->text().length() > ui->expression->cursorPosition() &&
      ui->expression->text().at(ui->expression->cursorPosition()) == ']') {
    ui->expression->cursorForward(false);
  } else {
    ui->expression->insert("]");
  }
}

void calculator::view::MathCalculator::on_factorial_clicked() {
  ui->expression->insert("!");
}

void calculator::view::MathCalculator::on_exponent_clicked() {
  ui->expression->insert("e");
}

void calculator::view::MathCalculator::on_x_button_clicked() {
  ui->expression->insert("x");
}

void calculator::view::MathCalculator::on_plus_clicked() {
  ui->expression->insert("+");
}

void calculator::view::MathCalculator::on_minus_clicked() {
  ui->expression->insert("-");
}

void calculator::view::MathCalculator::on_multiply_clicked() {
  ui->expression->insert("*");
}

void calculator::view::MathCalculator::on_divide_clicked() {
  ui->expression->insert("/");
}

void calculator::view::MathCalculator::on_int_mod_clicked() {
  ui->expression->insert("%");
}

void calculator::view::MathCalculator::on_mod_clicked() {
  ui->expression->insert("mod");
}

void calculator::view::MathCalculator::on_sqrt_clicked() {
  ui->expression->insert("sqrt()");
  ui->expression->cursorBackward(false);
}

void calculator::view::MathCalculator::SetupPlots() {
  ui->plot_area->setInteraction(QCP::iRangeDrag, true);
  ui->plot_area->setInteraction(QCP::iRangeZoom, true);
  ui->plot_area->setInteraction(QCP::iSelectPlottables, true);
  ui->plot_area->setInteraction(QCP::iSelectLegend, true);
  ui->plot_area->setInteraction(QCP::iSelectItems, true);
  ui->plot_area->setInteraction(QCP::iMultiSelect, true);
  ui->plot_area->xAxis->setLabel("x");
  ui->plot_area->yAxis->setLabel("y");
  ui->plot_area->xAxis2->setVisible(true);
  ui->plot_area->yAxis2->setVisible(true);
  ui->plot_area->axisRect()->insetLayout()->setInsetAlignment(
      0, Qt::AlignBottom | Qt::AlignRight);
  on_center_plot_clicked();
  ui->plot_color->addItems(QColor::colorNames());
  ui->plot_color->setCurrentText("blue");
}

QVector<double> calculator::view::MathCalculator::GetPlotRanges() {
  QVector<double> result;
  result.reserve(4);
  result.push_back(ui->x_min->value());
  result.push_back(ui->x_max->value());
  result.push_back(ui->y_min->value());
  result.push_back(ui->y_max->value());
  return result;
}

void calculator::view::MathCalculator::DrawPlot() {
  if (ui->autoclear_checkbox->isChecked()) on_clear_plot_clicked();
  SetUserOrDefaultRanges();
  QVector<double> x_values, y_values;
  x_values.reserve(kDefaultPlotDotCount);
  y_values.reserve(kDefaultPlotDotCount);
  double x = ui->plot_area->xAxis->range().lower;
  double step =
      (ui->plot_area->xAxis->range().upper - x) / kDefaultPlotDotCount;
  for (int i = 0; i < kDefaultPlotDotCount; ++i) {
    x_values.push_back(x);
    double y = controller->GetResult(x);
    if (y > ui->plot_area->yAxis->range().upper * kDefaultPlotSizeMultiplier ||
        y < ui->plot_area->yAxis->range().lower * kDefaultPlotSizeMultiplier) {
      y_values.push_back(NAN);
    } else {
      y_values.push_back(controller->GetResult(x));
    }
    x += step;
  }
  AddGraphToPlots(x_values, y_values);
}

void calculator::view::MathCalculator::SetRanges(
    const QVector<double> &ranges) {
  ui->plot_area->xAxis->setRange(ranges[0], ranges[1]);
  ui->plot_area->yAxis->setRange(ranges[2], ranges[3]);
}

void calculator::view::MathCalculator::SetUserOrDefaultRanges() {
  if (!ui->invalid_x_ranges_label->text().isEmpty() ||
      !ui->invalid_y_ranges_label->text().isEmpty()) {
    SetRanges(kDefaultRanges);
  } else {
    SetRanges(GetPlotRanges());
  }
}

void calculator::view::MathCalculator::AddGraphToPlots(
    const QVector<double> &x, const QVector<double> &y) {
  ui->plot_area->addGraph();
  if (ui->random_color_checkbox->isChecked()) {
    ui->plot_color->setCurrentIndex(
        QRandomGenerator::global()->bounded(ui->plot_color->count()));
  }
  ui->plot_area->graph(ui->plot_area->graphCount() - 1)
      ->setPen(QPen(QColor(ui->plot_color->currentText())));
  ui->plot_area->graph(ui->plot_area->graphCount() - 1)
      ->setName(ui->expression->text());
  ui->plot_area->graph(ui->plot_area->graphCount() - 1)->setData(x, y);
  ui->plot_area->replot();
}

void calculator::view::MathCalculator::SetupHistory() {
  connect(ui->history_table, &QTableWidget::itemDoubleClicked, this,
          &calculator::view::MathCalculator::InputExpressionFromHistory);
}

void calculator::view::MathCalculator::LogEvaluation(const QString &expression,
                                                     double x, double result) {
  ui->history_table->insertRow(ui->history_table->rowCount());
  ui->history_table->setItem(ui->history_table->rowCount() - 1, 2,
                             new QTableWidgetItem(expression));
  ui->history_table->setItem(ui->history_table->rowCount() - 1, 1,
                             new QTableWidgetItem(QString::number(x)));
  ui->history_table->setItem(ui->history_table->rowCount() - 1, 0,
                             new QTableWidgetItem(QString::number(result)));
}

void calculator::view::MathCalculator::on_reset_plot_ranges_clicked() {
  ui->x_min->setValue(kDefaultRanges[0]);
  ui->x_max->setValue(kDefaultRanges[1]);
  ui->y_min->setValue(kDefaultRanges[2]);
  ui->y_max->setValue(kDefaultRanges[3]);
  ui->plot_area->replot();
}

void calculator::view::MathCalculator::on_center_plot_clicked() {
  ui->plot_area->xAxis->setRange(ui->x_min->value(), ui->x_max->value());
  ui->plot_area->yAxis->setRange(ui->y_min->value(), ui->y_max->value());
  ui->plot_area->replot();
}

void calculator::view::MathCalculator::on_clear_plot_clicked() {
  ui->plot_area->clearGraphs();
  ui->plot_area->replot();
}

void calculator::view::MathCalculator::on_x_min_valueChanged(double arg1) {
  if (arg1 >= ui->x_max->value())
    ui->invalid_x_ranges_label->setText(kXRangeError);
  else
    ui->invalid_x_ranges_label->clear();
}

void calculator::view::MathCalculator::on_x_max_valueChanged(double arg1) {
  if (arg1 <= ui->x_min->value())
    ui->invalid_x_ranges_label->setText(kXRangeError);
  else
    ui->invalid_x_ranges_label->clear();
}

void calculator::view::MathCalculator::on_y_min_valueChanged(double arg1) {
  if (arg1 >= ui->y_max->value())
    ui->invalid_y_ranges_label->setText(kYRangeError);
  else
    ui->invalid_y_ranges_label->clear();
}

void calculator::view::MathCalculator::on_y_max_valueChanged(double arg1) {
  if (arg1 <= ui->y_min->value())
    ui->invalid_y_ranges_label->setText(kYRangeError);
  else
    ui->invalid_y_ranges_label->clear();
}

void calculator::view::MathCalculator::on_show_legend_clicked() {
  ui->plot_area->legend->setVisible(!ui->plot_area->legend->visible());
  ui->plot_area->replot();
}

void calculator::view::MathCalculator::on_clear_history_clicked() {
  ui->history_table->setRowCount(0);
}

void calculator::view::MathCalculator::InputExpressionFromHistory(
    QTableWidgetItem *item) {
  if (item->column() == 2 || item->column() == 0) {
    ui->expression->setText(item->text());
  } else {
    ui->x_input->setValue(item->text().toDouble());
  }
  QApplication::clipboard()->setText(item->text());
}

void calculator::view::MathCalculator::on_create_plot_checkbox_clicked() {
  ui->autoclear_checkbox->setEnabled(ui->create_plot_checkbox->isChecked());
}

void calculator::view::MathCalculator::on_actionCredit_triggered() {
  emit OpenCreditCalculator();
  hide();
}

void calculator::view::MathCalculator::on_actionDeposit_triggered() {
  emit OpenDepositCalculator();
  hide();
}

void calculator::view::MathCalculator::on_random_color_checkbox_stateChanged(
    int arg1) {
  ui->plot_color->setEnabled(!arg1);
}

void calculator::view::MathCalculator::on_x_input_editingFinished() {
  on_evaluate_clicked();
}

void calculator::view::MathCalculator::on_pushButton_clicked() {
  ui->expression->insert("^");
}
