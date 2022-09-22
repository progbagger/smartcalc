#include "mainwindow.h"

#include "ui_mainwindow.h"

#define push_symbol_without_brackets(digit)           \
  void MainWindow::on_digit_##digit##_clicked() {     \
    push_without_brackets(*ui->input_output, #digit); \
  }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->setMaximumHeight(this->height());
  this->setMinimumHeight(this->height());
  ui->setupUi(this);

  // Connecting slots to other windows
  connect(&this->credit_calculator, &credit::open_calculator, this,
          &MainWindow::credit_closed);
  connect(&this->credit_calculator, &credit::open_deposit, this,
          &MainWindow::from_credit_opened_deposit);
  connect(&this->deposit_calculator, &deposit::open_calculator, this,
          &MainWindow::deposit_closed);
  connect(&this->deposit_calculator, &deposit::open_credit, this,
          &MainWindow::from_deposit_opened_credit);

  // Resizing window and disabling history and plots on default
  on_plot_clicked();
  on_toggle_history_clicked();

  // Setting plot options
  ui->plot_graph->setInteraction(QCP::iRangeDrag, true);
  ui->plot_graph->setInteraction(QCP::iRangeZoom, true);
  ui->plot_graph->xAxis->setLabel("x");
  ui->plot_graph->xAxis->setRange(-25 + -25 / 10, 25 + 25 / 10);
  ui->plot_graph->yAxis->setLabel("y");
  ui->plot_graph->yAxis->setRange(-25 + -25 / 10, 25 + 25 / 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::hide_history() {
  ui->history->hide();
  ui->clear_history->hide();
  ui->history_label->hide();
  this->setGeometry(this->x(), this->y() + Y_MOVE_FACTOR, MIN_WIDTH,
                    this->height());
  this->setMinimumWidth(MIN_WIDTH);
  this->setMaximumWidth(MIN_WIDTH);
  this->setGeometry(this->x(), this->y() + Y_MOVE_FACTOR, MIN_WIDTH,
                    this->height());
}

void MainWindow::show_history() {
  ui->history->show();
  ui->clear_history->show();
  ui->history_label->show();
  this->setGeometry(this->x(), this->y() + Y_MOVE_FACTOR,
                    MIN_WIDTH_WITH_HISTORY, this->height());
  this->setMinimumWidth(MIN_WIDTH_WITH_HISTORY);
  this->setMaximumWidth(MIN_WIDTH_WITH_HISTORY);
  this->setGeometry(this->x(), this->y() + Y_MOVE_FACTOR,
                    MIN_WIDTH_WITH_HISTORY, this->height());
}

void MainWindow::hide_plot() {
  this->setMinimumWidth(MIN_WIDTH);
  this->setMaximumWidth(MIN_WIDTH);
  this->setGeometry(this->x(), this->y() + Y_MOVE_FACTOR, MIN_WIDTH,
                    this->height());
  ui->plot_graph->hide();
  ui->current_plot->hide();
  ui->clear_plots->hide();
  ui->center->hide();
  ui->x_range->hide();
  ui->y_range->hide();
  ui->x_range_label->hide();
  ui->y_range_label->hide();
}

void MainWindow::show_plot() {
  this->setMinimumWidth(MIN_WIDTH_WITH_PLOT);
  this->setMinimumWidth(MIN_WIDTH_WITH_PLOT);
  this->setGeometry(this->x(), this->y() + Y_MOVE_FACTOR, MIN_WIDTH_WITH_PLOT,
                    this->height());
  ui->plot_graph->show();
  ui->current_plot->show();
  ui->clear_plots->show();
  ui->center->show();
  ui->x_range->show();
  ui->y_range->show();
  ui->x_range_label->show();
  ui->y_range_label->show();
}

void MainWindow::on_erase_clicked(bool next_sym = false) {
  QTextCursor current_cursor = ui->input_output->textCursor();
  if (next_sym) {
    int curpos = current_cursor.position();
    current_cursor.movePosition(current_cursor.NextCharacter);
    if (curpos == current_cursor.position()) {
      ui->input_output->insertPlainText(" ");
    }
  }
  bool bracket_deleted = false;
  if (current_cursor.position() != 0) {
    if (ui->input_output->toPlainText().length() > current_cursor.position() &&
        ui->input_output->toPlainText()[current_cursor.position()] == ')' &&
        ui->input_output->toPlainText()[current_cursor.position() - 1] == '(') {
      bracket_deleted = true;
      current_cursor.deleteChar();
      //      ui->input_output->textCursor().deletePreviousChar();
      current_cursor.deletePreviousChar();
    }
    bool func_deleted = false;
    while (current_cursor.position() != 0 &&
           QString("sincostanlnlogsqrtmod")
               .contains(ui->input_output
                             ->toPlainText()[current_cursor.position() - 1])) {
      current_cursor.deletePreviousChar();
      func_deleted = true;
    }
    if (!func_deleted && !bracket_deleted) current_cursor.deletePreviousChar();
  }
  ui->input_output->setTextCursor(current_cursor);
}

void push_with_brackets(QTextEdit &field, QString value) {
  field.insertPlainText(value);
  QTextCursor current_cursor = field.textCursor();
  current_cursor.movePosition(current_cursor.Left);
  field.setTextCursor(current_cursor);
}

void push_without_brackets(QTextEdit &field, QString value) {
  if (value == ")") {
    QTextCursor current_cursor = field.textCursor();
    QString current_text = field.toPlainText();
    if (current_text.length() > current_cursor.position() &&
        current_text[current_cursor.position()] == ')') {
      current_cursor.setPosition(current_cursor.position() + 1);
      field.setTextCursor(current_cursor);
    } else {
      field.insertPlainText(value);
    }
  } else {
    field.insertPlainText(value);
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  enum keys_definitions {
    shift = 33554432,
    backspace = 16777219,
    equal = 16777220,
    del = 16777223
  };

  QString available_symbols = "xXm()1234567890./*-+^=";
  QString available_functions = "sctSCTqlL";
  QVector<QString> functions = {
      "sin()",  "cos()",  "tan()", "asin()", "acos()",
      "atan()", "sqrt()", "ln()",  "log()",
  };
  if (event->modifiers().toInt() == shift &&
      !available_symbols.contains(event->text()) &&
      !available_functions.contains(event->text()) &&
      !event->text().isEmpty()) {
    if (event->key() == backspace) {
      on_clear_clicked();
    } else if (event->text() == "H") {
      on_clear_history_clicked();
    }
  } else if (available_symbols.contains(event->text()) &&
             !event->text().isEmpty()) {
    if (event->text() == "(") {
      on_left_bracket_clicked();
    } else if (event->text() == "m") {
      on_mod_clicked();
    } else if (event->text() == "=") {
      on_equal_clicked();
    } else {
      if (event->text() == "X")
        push_without_brackets(*ui->input_output, "x");
      else
        push_without_brackets(*ui->input_output, event->text());
    }
  } else if (event->key() == backspace) {
    on_erase_clicked();
  } else if (event->key() == equal) {
    on_equal_clicked();
  } else if (event->key() == del) {
    on_erase_clicked(true);
  } else if (available_functions.contains(event->text()) &&
             !event->text().isEmpty()) {
    push_with_brackets(*ui->input_output,
                       functions[available_functions.indexOf(event->text())]);
  }
}

void MainWindow::on_sqrt_clicked() {
  push_with_brackets(*ui->input_output, "sqrt()");
}

void MainWindow::on_left_bracket_clicked() {
  push_with_brackets(*ui->input_output, "()");
}

void MainWindow::on_rigth_bracket_clicked() {
  push_without_brackets(*ui->input_output, ")");
}

void MainWindow::on_mod_clicked() {
  push_without_brackets(*ui->input_output, "mod");
}

void MainWindow::on_div_clicked() {
  push_without_brackets(*ui->input_output, "/");
}

void MainWindow::on_pow_clicked() {
  push_without_brackets(*ui->input_output, "^");
}

push_symbol_without_brackets(7);

push_symbol_without_brackets(8);

push_symbol_without_brackets(9);

void MainWindow::on_multiply_clicked() {
  push_without_brackets(*ui->input_output, "*");
}

void MainWindow::on_power_of_10_clicked() {
  push_without_brackets(*ui->input_output, "10^");
}

push_symbol_without_brackets(4);

push_symbol_without_brackets(5);

push_symbol_without_brackets(6);

void MainWindow::on_minus_clicked() {
  push_without_brackets(*ui->input_output, "-");
}

void MainWindow::on_log10_clicked() {
  push_with_brackets(*ui->input_output, "log()");
}

push_symbol_without_brackets(1);

push_symbol_without_brackets(2);

push_symbol_without_brackets(3);

void MainWindow::on_plus_clicked() {
  push_without_brackets(*ui->input_output, "+");
}

void MainWindow::on_ln_clicked() {
  push_with_brackets(*ui->input_output, "ln()");
}

push_symbol_without_brackets(0);

void MainWindow::on_dot_clicked() {
  push_without_brackets(*ui->input_output, ".");
}

QVector<QPair<double, double>> MainWindow::get_ranges() {
  double x_min = -25.0, x_max = 25.0;
  double y_min = -25.0, y_max = 25.0;

  // Checking for ranges

  // x range
  QRegularExpression reg(
      "^(?<min>\\-?\\d+(\\.\\d+)?) +(?<max>\\-?\\d+(\\.\\d+)?)$");
  QRegularExpressionMatch match = reg.match(ui->x_range->text());
  bool is_x_valid = true, is_y_valid = true;
  if (match.hasMatch()) {
    double x_min_readed = match.captured("min").toDouble();
    double x_max_readed = match.captured("max").toDouble();
    if (x_min_readed < x_max_readed && x_min_readed >= -1000000 &&
        x_max_readed <= 1000000) {
      x_min = x_min_readed;
      x_max = x_max_readed;
    } else {
      is_x_valid = false;
    }
  } else if (!ui->x_range->text().isEmpty()) {
    is_x_valid = false;
  }

  // y range
  match = reg.match(ui->y_range->text());
  if (match.hasMatch()) {
    double y_min_readed = match.captured("min").toDouble();
    double y_max_readed = match.captured("max").toDouble();
    if (y_min_readed < y_max_readed && y_min_readed >= -1000000 &&
        y_max_readed <= 1000000) {
      y_min = y_min_readed;
      y_max = y_max_readed;
    } else {
      is_y_valid = false;
      y_min = x_min;
      y_max = x_max;
    }
  } else if (!ui->y_range->text().isEmpty()) {
    is_y_valid = false;
  } else {
    y_min = x_min;
    y_max = x_max;
  }

  // Setting message in case of invalid ranges
  if (!is_x_valid) ui->is_x_range_valid->setText("x range invalid");
  if (!is_y_valid) ui->is_y_range_valid->setText("y range invalid");

  QPair<double, double> x(x_min, x_max), y(y_min, y_max);

  return QVector<QPair<double, double>>{x, y};
}

void MainWindow::create_graph(const char *expression, QString &name) {
  // Checking for ranges
  auto ranges = get_ranges();
  double x_min = ranges[0].first, x_max = ranges[0].second;
  double y_min = ranges[1].first, y_max = ranges[1].second;

  // Creating x and y table
  int plot_size = 10001;  // always 1 at the end so it can be translated on
                          // even amount of dots
  QVector<double> x(plot_size), y(plot_size);
  for (int i = 0; i < plot_size; i++) {
    x[i] = x_min + (x_max - x_min) / (plot_size - 1) * i;
    char *calculated_expr = calc_postfix(expression, x[i]);
    QString calculated_expr_str(calculated_expr);
    if (calculated_expr_str.contains("nan")) {
      y[i] = NAN;
    } else {
      y[i] = calculated_expr_str.toDouble();
    }
    delete calculated_expr;
  }

  // Drawing plot
  ui->plot_graph->clearGraphs();
  QCPGraph *current_graph = ui->plot_graph->addGraph();
  current_graph->addData(x, y);
  current_graph->setName(name);
  current_graph->setPen(QPen(QColor("Green")));
  current_graph->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
  current_graph->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDiamond, 2.3));
  ui->plot_graph->xAxis->setRange(x_min - fabs(x_min / 10),
                                  x_max + fabs(x_max / 10));
  ui->plot_graph->yAxis->setRange(y_min - fabs(y_min / 10),
                                  fabs(y_max + y_max / 10));
  ui->plot_graph->replot();
}

void MainWindow::on_equal_clicked() {
  QString expression = ui->input_output->toPlainText();
  std::string expr = expression.toStdString();
  char *postfix = expr.data();
  postfix = infix_to_postfix(postfix);
  QString x_value = ui->x_value->text();
  double x;
  if (x_value.contains(QRegularExpression("^-?\\d+(\\.\\d+)?$")) ||
      x_value.isEmpty()) {
    x = x_value.toDouble();
    ui->x_error_msg->clear();
  } else {
    x = 0;  // default
    ui->x_error_msg->setText("x value error");
  }
  char *result = NULL;

  if (postfix) {
    result = calc_postfix(postfix, x);
    if (result) {
      if (!expression.contains("x") ||
          (!x_value.isEmpty() && ui->x_error_msg->text().isEmpty())) {
        ui->input_output->clear();
        if (strcmp(result, "0")) ui->input_output->append(result);
        if (!x_value.isEmpty() && ui->x_error_msg->text().isEmpty() &&
            expression.contains("x"))
          ui->history->append(expression + "(x=" + QString::number(x) + ")" +
                              "=" + result);
        else
          ui->history->append(expression + "=" + result);
      } else {
        ui->history->append(expression);
      }

      ui->history->append("");
    } else {
      ui->calc_error_msg->setText("Fatal error during calculation");
    }
  }

  if (!postfix || !result) {
    ui->calc_error_msg->setText("Calculation error");
  } else {
    if (!ui->plot_graph->isHidden()) {
      // Outputing current expression
      ui->current_plot->setText(expression);

      // Creating x and y table and drawing plot
      this->create_graph(postfix, expression);
    }
  }
  delete postfix;
  delete result;
}

void MainWindow::on_sin_clicked() {
  push_with_brackets(*ui->input_output, "sin()");
}

void MainWindow::on_cos_clicked() {
  push_with_brackets(*ui->input_output, "cos()");
}

void MainWindow::on_tan_clicked() {
  push_with_brackets(*ui->input_output, "tan()");
}

void MainWindow::on_asin_clicked() {
  push_with_brackets(*ui->input_output, "asin()");
}

void MainWindow::on_acos_clicked() {
  push_with_brackets(*ui->input_output, "acos()");
}

void MainWindow::on_atan_clicked() {
  push_with_brackets(*ui->input_output, "atan()");
}

void MainWindow::on_clear_history_clicked() { ui->history->clear(); }

void MainWindow::on_clear_clicked() {
  ui->input_output->clear();
  ui->x_value->clear();
}

void MainWindow::on_x_value_textChanged() { ui->x_error_msg->clear(); }

void MainWindow::on_plot_clicked() {
  if (ui->plot_graph->isHidden()) {
    if (!ui->history->isHidden()) on_toggle_history_clicked();
    show_plot();
  } else {
    hide_plot();
  }
}

void MainWindow::on_toggle_history_clicked() {
  if (ui->history->isHidden()) {
    if (!ui->plot_graph->isHidden()) on_plot_clicked();
    show_history();
  } else {
    hide_history();
  }
}

void MainWindow::on_input_output_textChanged() {
  ui->calc_error_msg->clear();
  QString current_text = ui->input_output->toPlainText();
  if (current_text.length() >= 256) {
    current_text.chop(current_text.length() - 256 + 1);
    ui->input_output->clear();
    ui->input_output->append(current_text);
    ui->calc_error_msg->setText("Only 255 symbols affordable");
  }
}

void MainWindow::on_clear_plots_clicked() {
  ui->plot_graph->clearGraphs();
  ui->plot_graph->replot();
  ui->current_plot->clear();
  on_center_clicked();
}

void MainWindow::on_center_clicked() {
  auto ranges = get_ranges();
  ui->plot_graph->xAxis->setRange(ranges[0].first, ranges[0].second);
  ui->plot_graph->yAxis->setRange(ranges[1].first, ranges[1].second);
  ui->plot_graph->replot();
}

void MainWindow::on_x_button_clicked() {
  ui->input_output->insertPlainText("x");
}

void MainWindow::on_x_range_textEdited() { ui->is_x_range_valid->clear(); }

void MainWindow::on_y_range_textEdited() { ui->is_y_range_valid->clear(); }

void MainWindow::on_actionCredit_triggered() {
  credit_calculator.show();
  credit_calculator.setGeometry(this->x(), this->y() + Y_MOVE_FACTOR,
                                credit_calculator.geometry().width(),
                                credit_calculator.geometry().height());
  this->hide();
}

void MainWindow::on_actionDeposit_triggered() {
  deposit_calculator.show();
  deposit_calculator.setGeometry(this->x(), this->y() + Y_MOVE_FACTOR,
                                 deposit_calculator.geometry().width(),
                                 deposit_calculator.geometry().height());
  this->hide();
}

void MainWindow::credit_closed() {
  this->setGeometry(this->credit_calculator.geometry().x(),
                    this->credit_calculator.geometry().y(),
                    this->geometry().width(), this->geometry().height());
  this->show();
}

void MainWindow::from_credit_opened_deposit() {
  this->credit_closed();
  this->on_actionDeposit_triggered();
}

void MainWindow::deposit_closed() {
  this->setGeometry(this->deposit_calculator.geometry().x(),
                    this->deposit_calculator.geometry().y(),
                    this->geometry().width(), this->geometry().height());
  this->show();
}

void MainWindow::from_deposit_opened_credit() {
  this->deposit_closed();
  this->on_actionCredit_triggered();
}

void MainWindow::on_x_clear_clicked() { ui->x_value->clear(); }
