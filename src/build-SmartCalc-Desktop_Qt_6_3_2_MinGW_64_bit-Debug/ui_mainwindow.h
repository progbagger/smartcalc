/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCredit;
    QAction *actionDeposit;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *buttons;
    QPushButton *sqrt;
    QPushButton *digit_2;
    QPushButton *sin;
    QPushButton *mod;
    QPushButton *pow;
    QPushButton *dot;
    QPushButton *digit_8;
    QPushButton *digit_7;
    QPushButton *acos;
    QPushButton *tan;
    QPushButton *digit_6;
    QPushButton *plus;
    QPushButton *power_of_10;
    QPushButton *digit_4;
    QPushButton *rigth_bracket;
    QPushButton *cos;
    QPushButton *atan;
    QPushButton *multiply;
    QPushButton *equal;
    QPushButton *log10;
    QPushButton *digit_0;
    QPushButton *digit_3;
    QPushButton *minus;
    QPushButton *digit_1;
    QPushButton *left_bracket;
    QPushButton *asin;
    QPushButton *digit_9;
    QPushButton *ln;
    QPushButton *div;
    QPushButton *digit_5;
    QPushButton *erase;
    QPushButton *clear;
    QPushButton *x_button;
    QTextEdit *input_output;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *x_buttons;
    QLineEdit *x_value;
    QPushButton *x_clear;
    QPushButton *plot;
    QPushButton *toggle_history;
    QTextEdit *history;
    QLabel *history_label;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *clear_history;
    QWidget *gridLayoutWidget_2;
    QGridLayout *error_messages;
    QLabel *x_error_msg;
    QLabel *calc_error_msg;
    QCustomPlot *plot_graph;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *plot_buttons;
    QPushButton *center;
    QPushButton *clear_plots;
    QLabel *current_plot;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *ranges;
    QHBoxLayout *ranges_with_labels;
    QLabel *x_range_label;
    QLineEdit *x_range;
    QLabel *y_range_label;
    QLineEdit *y_range;
    QHBoxLayout *is_ranges_valid;
    QLabel *is_x_range_valid;
    QLabel *is_y_range_valid;
    QMenuBar *menuBar;
    QMenu *menuMode;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 572);
        MainWindow->setMinimumSize(QSize(878, 572));
        QFont font;
        font.setFamilies({QString::fromUtf8("Fira Code")});
        font.setPointSize(12);
        font.setBold(true);
        MainWindow->setFont(font);
        actionCredit = new QAction(MainWindow);
        actionCredit->setObjectName(QString::fromUtf8("actionCredit"));
        actionCredit->setCheckable(false);
        actionDeposit = new QAction(MainWindow);
        actionDeposit->setObjectName(QString::fromUtf8("actionDeposit"));
        actionDeposit->setCheckable(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 180, 641, 341));
        buttons = new QGridLayout(gridLayoutWidget);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setHorizontalSpacing(16);
        buttons->setContentsMargins(8, 0, 8, 0);
        sqrt = new QPushButton(gridLayoutWidget);
        sqrt->setObjectName(QString::fromUtf8("sqrt"));

        buttons->addWidget(sqrt, 1, 1, 1, 1);

        digit_2 = new QPushButton(gridLayoutWidget);
        digit_2->setObjectName(QString::fromUtf8("digit_2"));

        buttons->addWidget(digit_2, 4, 3, 1, 1);

        sin = new QPushButton(gridLayoutWidget);
        sin->setObjectName(QString::fromUtf8("sin"));

        buttons->addWidget(sin, 0, 0, 1, 1);

        mod = new QPushButton(gridLayoutWidget);
        mod->setObjectName(QString::fromUtf8("mod"));

        buttons->addWidget(mod, 1, 4, 1, 1);

        pow = new QPushButton(gridLayoutWidget);
        pow->setObjectName(QString::fromUtf8("pow"));

        buttons->addWidget(pow, 2, 1, 1, 1);

        dot = new QPushButton(gridLayoutWidget);
        dot->setObjectName(QString::fromUtf8("dot"));

        buttons->addWidget(dot, 5, 4, 1, 1);

        digit_8 = new QPushButton(gridLayoutWidget);
        digit_8->setObjectName(QString::fromUtf8("digit_8"));

        buttons->addWidget(digit_8, 2, 3, 1, 1);

        digit_7 = new QPushButton(gridLayoutWidget);
        digit_7->setObjectName(QString::fromUtf8("digit_7"));

        buttons->addWidget(digit_7, 2, 2, 1, 1);

        acos = new QPushButton(gridLayoutWidget);
        acos->setObjectName(QString::fromUtf8("acos"));

        buttons->addWidget(acos, 4, 0, 1, 1);

        tan = new QPushButton(gridLayoutWidget);
        tan->setObjectName(QString::fromUtf8("tan"));

        buttons->addWidget(tan, 2, 0, 1, 1);

        digit_6 = new QPushButton(gridLayoutWidget);
        digit_6->setObjectName(QString::fromUtf8("digit_6"));

        buttons->addWidget(digit_6, 3, 4, 1, 1);

        plus = new QPushButton(gridLayoutWidget);
        plus->setObjectName(QString::fromUtf8("plus"));

        buttons->addWidget(plus, 4, 5, 1, 1);

        power_of_10 = new QPushButton(gridLayoutWidget);
        power_of_10->setObjectName(QString::fromUtf8("power_of_10"));

        buttons->addWidget(power_of_10, 3, 1, 1, 1);

        digit_4 = new QPushButton(gridLayoutWidget);
        digit_4->setObjectName(QString::fromUtf8("digit_4"));

        buttons->addWidget(digit_4, 3, 2, 1, 1);

        rigth_bracket = new QPushButton(gridLayoutWidget);
        rigth_bracket->setObjectName(QString::fromUtf8("rigth_bracket"));

        buttons->addWidget(rigth_bracket, 1, 3, 1, 1);

        cos = new QPushButton(gridLayoutWidget);
        cos->setObjectName(QString::fromUtf8("cos"));

        buttons->addWidget(cos, 1, 0, 1, 1);

        atan = new QPushButton(gridLayoutWidget);
        atan->setObjectName(QString::fromUtf8("atan"));

        buttons->addWidget(atan, 5, 0, 1, 1);

        multiply = new QPushButton(gridLayoutWidget);
        multiply->setObjectName(QString::fromUtf8("multiply"));

        buttons->addWidget(multiply, 2, 5, 1, 1);

        equal = new QPushButton(gridLayoutWidget);
        equal->setObjectName(QString::fromUtf8("equal"));

        buttons->addWidget(equal, 5, 5, 1, 1);

        log10 = new QPushButton(gridLayoutWidget);
        log10->setObjectName(QString::fromUtf8("log10"));

        buttons->addWidget(log10, 4, 1, 1, 1);

        digit_0 = new QPushButton(gridLayoutWidget);
        digit_0->setObjectName(QString::fromUtf8("digit_0"));

        buttons->addWidget(digit_0, 5, 3, 1, 1);

        digit_3 = new QPushButton(gridLayoutWidget);
        digit_3->setObjectName(QString::fromUtf8("digit_3"));

        buttons->addWidget(digit_3, 4, 4, 1, 1);

        minus = new QPushButton(gridLayoutWidget);
        minus->setObjectName(QString::fromUtf8("minus"));

        buttons->addWidget(minus, 3, 5, 1, 1);

        digit_1 = new QPushButton(gridLayoutWidget);
        digit_1->setObjectName(QString::fromUtf8("digit_1"));

        buttons->addWidget(digit_1, 4, 2, 1, 1);

        left_bracket = new QPushButton(gridLayoutWidget);
        left_bracket->setObjectName(QString::fromUtf8("left_bracket"));

        buttons->addWidget(left_bracket, 1, 2, 1, 1);

        asin = new QPushButton(gridLayoutWidget);
        asin->setObjectName(QString::fromUtf8("asin"));

        buttons->addWidget(asin, 3, 0, 1, 1);

        digit_9 = new QPushButton(gridLayoutWidget);
        digit_9->setObjectName(QString::fromUtf8("digit_9"));

        buttons->addWidget(digit_9, 2, 4, 1, 1);

        ln = new QPushButton(gridLayoutWidget);
        ln->setObjectName(QString::fromUtf8("ln"));

        buttons->addWidget(ln, 5, 1, 1, 1);

        div = new QPushButton(gridLayoutWidget);
        div->setObjectName(QString::fromUtf8("div"));

        buttons->addWidget(div, 1, 5, 1, 1);

        digit_5 = new QPushButton(gridLayoutWidget);
        digit_5->setObjectName(QString::fromUtf8("digit_5"));

        buttons->addWidget(digit_5, 3, 3, 1, 1);

        erase = new QPushButton(gridLayoutWidget);
        erase->setObjectName(QString::fromUtf8("erase"));

        buttons->addWidget(erase, 0, 4, 1, 1);

        clear = new QPushButton(gridLayoutWidget);
        clear->setObjectName(QString::fromUtf8("clear"));

        buttons->addWidget(clear, 0, 5, 1, 1);

        x_button = new QPushButton(gridLayoutWidget);
        x_button->setObjectName(QString::fromUtf8("x_button"));

        buttons->addWidget(x_button, 5, 2, 1, 1);

        input_output = new QTextEdit(centralwidget);
        input_output->setObjectName(QString::fromUtf8("input_output"));
        input_output->setEnabled(true);
        input_output->setGeometry(QRect(10, 20, 641, 81));
        input_output->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        input_output->setTabChangesFocus(true);
        input_output->setReadOnly(true);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 110, 641, 41));
        x_buttons = new QHBoxLayout(horizontalLayoutWidget);
        x_buttons->setSpacing(16);
        x_buttons->setObjectName(QString::fromUtf8("x_buttons"));
        x_buttons->setContentsMargins(8, 0, 8, 0);
        x_value = new QLineEdit(horizontalLayoutWidget);
        x_value->setObjectName(QString::fromUtf8("x_value"));

        x_buttons->addWidget(x_value);

        x_clear = new QPushButton(horizontalLayoutWidget);
        x_clear->setObjectName(QString::fromUtf8("x_clear"));

        x_buttons->addWidget(x_clear);

        plot = new QPushButton(horizontalLayoutWidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setMaximumSize(QSize(16777215, 16777215));

        x_buttons->addWidget(plot);

        toggle_history = new QPushButton(horizontalLayoutWidget);
        toggle_history->setObjectName(QString::fromUtf8("toggle_history"));

        x_buttons->addWidget(toggle_history);

        history = new QTextEdit(centralwidget);
        history->setObjectName(QString::fromUtf8("history"));
        history->setEnabled(true);
        history->setGeometry(QRect(660, 90, 211, 411));
        history->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        history->setAcceptDrops(false);
        history->setLayoutDirection(Qt::LeftToRight);
        history->setReadOnly(true);
        history_label = new QLabel(centralwidget);
        history_label->setObjectName(QString::fromUtf8("history_label"));
        history_label->setEnabled(true);
        history_label->setGeometry(QRect(660, 20, 211, 21));
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(660, 50, 211, 39));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setSpacing(16);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(8, 0, 8, 0);
        clear_history = new QPushButton(horizontalLayoutWidget_2);
        clear_history->setObjectName(QString::fromUtf8("clear_history"));
        clear_history->setEnabled(true);

        horizontalLayout->addWidget(clear_history);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 150, 641, 31));
        error_messages = new QGridLayout(gridLayoutWidget_2);
        error_messages->setObjectName(QString::fromUtf8("error_messages"));
        error_messages->setHorizontalSpacing(40);
        error_messages->setContentsMargins(0, 0, 0, 0);
        x_error_msg = new QLabel(gridLayoutWidget_2);
        x_error_msg->setObjectName(QString::fromUtf8("x_error_msg"));
        x_error_msg->setStyleSheet(QString::fromUtf8("color: red"));

        error_messages->addWidget(x_error_msg, 0, 0, 1, 1);

        calc_error_msg = new QLabel(gridLayoutWidget_2);
        calc_error_msg->setObjectName(QString::fromUtf8("calc_error_msg"));
        calc_error_msg->setStyleSheet(QString::fromUtf8("color: red"));

        error_messages->addWidget(calc_error_msg, 0, 1, 1, 1);

        plot_graph = new QCustomPlot(centralwidget);
        plot_graph->setObjectName(QString::fromUtf8("plot_graph"));
        plot_graph->setEnabled(true);
        plot_graph->setGeometry(QRect(660, 60, 611, 441));
        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(960, 21, 311, 39));
        plot_buttons = new QHBoxLayout(horizontalLayoutWidget_3);
        plot_buttons->setSpacing(16);
        plot_buttons->setObjectName(QString::fromUtf8("plot_buttons"));
        plot_buttons->setContentsMargins(8, 0, 8, 0);
        center = new QPushButton(horizontalLayoutWidget_3);
        center->setObjectName(QString::fromUtf8("center"));

        plot_buttons->addWidget(center);

        clear_plots = new QPushButton(horizontalLayoutWidget_3);
        clear_plots->setObjectName(QString::fromUtf8("clear_plots"));

        plot_buttons->addWidget(clear_plots);

        current_plot = new QLabel(centralwidget);
        current_plot->setObjectName(QString::fromUtf8("current_plot"));
        current_plot->setGeometry(QRect(660, 25, 291, 20));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(800, 500, 341, 75));
        ranges = new QVBoxLayout(verticalLayoutWidget);
        ranges->setSpacing(0);
        ranges->setObjectName(QString::fromUtf8("ranges"));
        ranges->setContentsMargins(0, 0, 0, 0);
        ranges_with_labels = new QHBoxLayout();
        ranges_with_labels->setObjectName(QString::fromUtf8("ranges_with_labels"));
        ranges_with_labels->setContentsMargins(-1, 10, -1, -1);
        x_range_label = new QLabel(verticalLayoutWidget);
        x_range_label->setObjectName(QString::fromUtf8("x_range_label"));

        ranges_with_labels->addWidget(x_range_label);

        x_range = new QLineEdit(verticalLayoutWidget);
        x_range->setObjectName(QString::fromUtf8("x_range"));
        x_range->setMinimumSize(QSize(0, 25));
        x_range->setFocusPolicy(Qt::ClickFocus);
        x_range->setClearButtonEnabled(false);

        ranges_with_labels->addWidget(x_range);

        y_range_label = new QLabel(verticalLayoutWidget);
        y_range_label->setObjectName(QString::fromUtf8("y_range_label"));

        ranges_with_labels->addWidget(y_range_label);

        y_range = new QLineEdit(verticalLayoutWidget);
        y_range->setObjectName(QString::fromUtf8("y_range"));
        y_range->setMinimumSize(QSize(0, 25));

        ranges_with_labels->addWidget(y_range);


        ranges->addLayout(ranges_with_labels);

        is_ranges_valid = new QHBoxLayout();
        is_ranges_valid->setObjectName(QString::fromUtf8("is_ranges_valid"));
        is_x_range_valid = new QLabel(verticalLayoutWidget);
        is_x_range_valid->setObjectName(QString::fromUtf8("is_x_range_valid"));
        is_x_range_valid->setStyleSheet(QString::fromUtf8("color: red"));

        is_ranges_valid->addWidget(is_x_range_valid);

        is_y_range_valid = new QLabel(verticalLayoutWidget);
        is_y_range_valid->setObjectName(QString::fromUtf8("is_y_range_valid"));
        is_y_range_valid->setStyleSheet(QString::fromUtf8("color: red"));

        is_ranges_valid->addWidget(is_y_range_valid);


        ranges->addLayout(is_ranges_valid);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 31));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QString::fromUtf8("menuMode"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMode->menuAction());
        menuMode->addAction(actionCredit);
        menuMode->addAction(actionDeposit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SmartCalc", nullptr));
        actionCredit->setText(QCoreApplication::translate("MainWindow", "Credit", nullptr));
        actionDeposit->setText(QCoreApplication::translate("MainWindow", "Deposit", nullptr));
        sqrt->setText(QCoreApplication::translate("MainWindow", "\342\210\232(x)", nullptr));
        digit_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        sin->setText(QCoreApplication::translate("MainWindow", "sin(x)", nullptr));
        mod->setText(QCoreApplication::translate("MainWindow", "mod", nullptr));
        pow->setText(QCoreApplication::translate("MainWindow", "x^y", nullptr));
        dot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        digit_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        digit_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        acos->setText(QCoreApplication::translate("MainWindow", "acos(x)", nullptr));
        tan->setText(QCoreApplication::translate("MainWindow", "tan(x)", nullptr));
        digit_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        plus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        power_of_10->setText(QCoreApplication::translate("MainWindow", "10^x", nullptr));
        digit_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        rigth_bracket->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        cos->setText(QCoreApplication::translate("MainWindow", "cos(x)", nullptr));
        atan->setText(QCoreApplication::translate("MainWindow", "atan(x)", nullptr));
        multiply->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        equal->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        log10->setText(QCoreApplication::translate("MainWindow", "log10(x)", nullptr));
        digit_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        digit_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        minus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        digit_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        left_bracket->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        asin->setText(QCoreApplication::translate("MainWindow", "asin(x)", nullptr));
        digit_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        ln->setText(QCoreApplication::translate("MainWindow", "ln(x)", nullptr));
        div->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        digit_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        erase->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "A/C", nullptr));
        x_button->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        input_output->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
        x_value->setPlaceholderText(QCoreApplication::translate("MainWindow", "Input x here", nullptr));
        x_clear->setText(QCoreApplication::translate("MainWindow", "Clear x", nullptr));
        plot->setText(QCoreApplication::translate("MainWindow", "Plot", nullptr));
        toggle_history->setText(QCoreApplication::translate("MainWindow", "History", nullptr));
        history->setPlaceholderText(QCoreApplication::translate("MainWindow", "...", nullptr));
        history_label->setText(QCoreApplication::translate("MainWindow", "History", nullptr));
        clear_history->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        x_error_msg->setText(QString());
        calc_error_msg->setText(QString());
        center->setText(QCoreApplication::translate("MainWindow", "Center", nullptr));
        clear_plots->setText(QCoreApplication::translate("MainWindow", "Clear plots", nullptr));
        current_plot->setText(QString());
        x_range_label->setText(QCoreApplication::translate("MainWindow", "x \342\210\210", nullptr));
        x_range->setPlaceholderText(QCoreApplication::translate("MainWindow", "-25 25", nullptr));
        y_range_label->setText(QCoreApplication::translate("MainWindow", "y \342\210\210", nullptr));
        y_range->setPlaceholderText(QString());
        is_x_range_valid->setText(QString());
        is_y_range_valid->setText(QString());
        menuMode->setTitle(QCoreApplication::translate("MainWindow", "Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
