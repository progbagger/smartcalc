/********************************************************************************
** Form generated from reading UI file 'deposit.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSIT_H
#define UI_DEPOSIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deposit
{
public:
    QAction *actionCalc;
    QAction *actionCredit;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *sum_label;
    QLabel *rate_label;
    QLabel *term_label;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *sum_input;
    QDoubleSpinBox *rate_input;
    QSpinBox *term_input;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *rate_type_label;
    QLabel *term_type_label;
    QVBoxLayout *verticalLayout_4;
    QComboBox *rate_type_input;
    QComboBox *term_type_input;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *calculate;
    QPushButton *clear;
    QTableWidget *output_table;
    QMenuBar *menuBar;
    QMenu *menuMode;

    void setupUi(QMainWindow *deposit)
    {
        if (deposit->objectName().isEmpty())
            deposit->setObjectName(QString::fromUtf8("deposit"));
        deposit->resize(642, 580);
        deposit->setMinimumSize(QSize(642, 580));
        deposit->setMaximumSize(QSize(642, 580));
        QFont font;
        font.setFamilies({QString::fromUtf8("Fira Code")});
        font.setPointSize(12);
        font.setBold(true);
        deposit->setFont(font);
        actionCalc = new QAction(deposit);
        actionCalc->setObjectName(QString::fromUtf8("actionCalc"));
        actionCalc->setCheckable(false);
        actionCredit = new QAction(deposit);
        actionCredit->setObjectName(QString::fromUtf8("actionCredit"));
        actionCredit->setCheckable(false);
        centralwidget = new QWidget(deposit);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget_5 = new QWidget(centralwidget);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(10, 10, 621, 531));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        sum_label = new QLabel(verticalLayoutWidget_5);
        sum_label->setObjectName(QString::fromUtf8("sum_label"));

        verticalLayout->addWidget(sum_label);

        rate_label = new QLabel(verticalLayoutWidget_5);
        rate_label->setObjectName(QString::fromUtf8("rate_label"));

        verticalLayout->addWidget(rate_label);

        term_label = new QLabel(verticalLayoutWidget_5);
        term_label->setObjectName(QString::fromUtf8("term_label"));

        verticalLayout->addWidget(term_label);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        sum_input = new QDoubleSpinBox(verticalLayoutWidget_5);
        sum_input->setObjectName(QString::fromUtf8("sum_input"));
        sum_input->setDecimals(2);
        sum_input->setMinimum(1000.000000000000000);
        sum_input->setMaximum(100000000.000000000000000);
        sum_input->setSingleStep(100.000000000000000);
        sum_input->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

        verticalLayout_2->addWidget(sum_input);

        rate_input = new QDoubleSpinBox(verticalLayoutWidget_5);
        rate_input->setObjectName(QString::fromUtf8("rate_input"));
        rate_input->setDecimals(2);
        rate_input->setMinimum(0.010000000000000);
        rate_input->setMaximum(10000000.000000000000000);
        rate_input->setSingleStep(100.000000000000000);
        rate_input->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

        verticalLayout_2->addWidget(rate_input);

        term_input = new QSpinBox(verticalLayoutWidget_5);
        term_input->setObjectName(QString::fromUtf8("term_input"));
        term_input->setMinimum(1);

        verticalLayout_2->addWidget(term_input);


        horizontalLayout_6->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        rate_type_label = new QLabel(verticalLayoutWidget_5);
        rate_type_label->setObjectName(QString::fromUtf8("rate_type_label"));

        verticalLayout_3->addWidget(rate_type_label);

        term_type_label = new QLabel(verticalLayoutWidget_5);
        term_type_label->setObjectName(QString::fromUtf8("term_type_label"));

        verticalLayout_3->addWidget(term_type_label);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        rate_type_input = new QComboBox(verticalLayoutWidget_5);
        rate_type_input->addItem(QString());
        rate_type_input->addItem(QString());
        rate_type_input->setObjectName(QString::fromUtf8("rate_type_input"));

        verticalLayout_4->addWidget(rate_type_input);

        term_type_input = new QComboBox(verticalLayoutWidget_5);
        term_type_input->addItem(QString());
        term_type_input->addItem(QString());
        term_type_input->setObjectName(QString::fromUtf8("term_type_input"));

        verticalLayout_4->addWidget(term_type_input);


        horizontalLayout_2->addLayout(verticalLayout_4);


        horizontalLayout->addLayout(horizontalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        calculate = new QPushButton(verticalLayoutWidget_5);
        calculate->setObjectName(QString::fromUtf8("calculate"));

        horizontalLayout_3->addWidget(calculate);

        clear = new QPushButton(verticalLayoutWidget_5);
        clear->setObjectName(QString::fromUtf8("clear"));

        horizontalLayout_3->addWidget(clear);


        verticalLayout_5->addLayout(horizontalLayout_3);

        output_table = new QTableWidget(verticalLayoutWidget_5);
        output_table->setObjectName(QString::fromUtf8("output_table"));

        verticalLayout_5->addWidget(output_table);

        deposit->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(deposit);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 642, 24));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QString::fromUtf8("menuMode"));
        deposit->setMenuBar(menuBar);

        menuBar->addAction(menuMode->menuAction());
        menuMode->addAction(actionCalc);
        menuMode->addAction(actionCredit);

        retranslateUi(deposit);

        QMetaObject::connectSlotsByName(deposit);
    } // setupUi

    void retranslateUi(QMainWindow *deposit)
    {
        deposit->setWindowTitle(QCoreApplication::translate("deposit", "Deposit calculator", nullptr));
        actionCalc->setText(QCoreApplication::translate("deposit", "Calc", nullptr));
        actionCredit->setText(QCoreApplication::translate("deposit", "Credit", nullptr));
        sum_label->setText(QCoreApplication::translate("deposit", "Sum", nullptr));
        rate_label->setText(QCoreApplication::translate("deposit", "Rate(%)", nullptr));
        term_label->setText(QCoreApplication::translate("deposit", "Term", nullptr));
        rate_type_label->setText(QCoreApplication::translate("deposit", "Rate type", nullptr));
        term_type_label->setText(QCoreApplication::translate("deposit", "Term type", nullptr));
        rate_type_input->setItemText(0, QCoreApplication::translate("deposit", "Per annum", nullptr));
        rate_type_input->setItemText(1, QCoreApplication::translate("deposit", "Monthly", nullptr));

        term_type_input->setItemText(0, QCoreApplication::translate("deposit", "Month", nullptr));
        term_type_input->setItemText(1, QCoreApplication::translate("deposit", "Years", nullptr));

        calculate->setText(QCoreApplication::translate("deposit", "Calculate", nullptr));
        clear->setText(QCoreApplication::translate("deposit", "Clear", nullptr));
        menuMode->setTitle(QCoreApplication::translate("deposit", "Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deposit: public Ui_deposit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSIT_H
