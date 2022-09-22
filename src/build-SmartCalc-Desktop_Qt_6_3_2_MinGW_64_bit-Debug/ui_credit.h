/********************************************************************************
** Form generated from reading UI file 'credit.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDIT_H
#define UI_CREDIT_H

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

class Ui_credit
{
public:
    QAction *actionCalc;
    QAction *actionDeposit;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *sum_label;
    QLabel *rate_label;
    QLabel *term_label;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *sum_input;
    QDoubleSpinBox *rate_input;
    QSpinBox *term_input;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *type_label;
    QLabel *rate_type_label;
    QLabel *term_type_label;
    QVBoxLayout *verticalLayout_4;
    QComboBox *type_input;
    QComboBox *rate_type_input;
    QComboBox *term_type_input;
    QHBoxLayout *horizontalLayout;
    QPushButton *calculate;
    QPushButton *clear;
    QTableWidget *output_table;
    QMenuBar *menuBar;
    QMenu *menuMode;

    void setupUi(QMainWindow *credit)
    {
        if (credit->objectName().isEmpty())
            credit->setObjectName(QString::fromUtf8("credit"));
        credit->resize(642, 580);
        credit->setMinimumSize(QSize(642, 580));
        credit->setMaximumSize(QSize(642, 580));
        QFont font;
        font.setFamilies({QString::fromUtf8("Fira Code")});
        font.setPointSize(12);
        font.setBold(true);
        credit->setFont(font);
        actionCalc = new QAction(credit);
        actionCalc->setObjectName(QString::fromUtf8("actionCalc"));
        actionCalc->setCheckable(false);
        actionDeposit = new QAction(credit);
        actionDeposit->setObjectName(QString::fromUtf8("actionDeposit"));
        actionDeposit->setCheckable(false);
        centralwidget = new QWidget(credit);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget_5 = new QWidget(centralwidget);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(10, 10, 622, 531));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
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


        horizontalLayout_2->addLayout(verticalLayout);

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


        horizontalLayout_2->addLayout(verticalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        type_label = new QLabel(verticalLayoutWidget_5);
        type_label->setObjectName(QString::fromUtf8("type_label"));

        verticalLayout_3->addWidget(type_label);

        rate_type_label = new QLabel(verticalLayoutWidget_5);
        rate_type_label->setObjectName(QString::fromUtf8("rate_type_label"));

        verticalLayout_3->addWidget(rate_type_label);

        term_type_label = new QLabel(verticalLayoutWidget_5);
        term_type_label->setObjectName(QString::fromUtf8("term_type_label"));

        verticalLayout_3->addWidget(term_type_label);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        type_input = new QComboBox(verticalLayoutWidget_5);
        type_input->addItem(QString());
        type_input->addItem(QString());
        type_input->setObjectName(QString::fromUtf8("type_input"));

        verticalLayout_4->addWidget(type_input);

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


        horizontalLayout_3->addLayout(verticalLayout_4);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        calculate = new QPushButton(verticalLayoutWidget_5);
        calculate->setObjectName(QString::fromUtf8("calculate"));

        horizontalLayout->addWidget(calculate);

        clear = new QPushButton(verticalLayoutWidget_5);
        clear->setObjectName(QString::fromUtf8("clear"));

        horizontalLayout->addWidget(clear);


        verticalLayout_5->addLayout(horizontalLayout);

        output_table = new QTableWidget(verticalLayoutWidget_5);
        output_table->setObjectName(QString::fromUtf8("output_table"));

        verticalLayout_5->addWidget(output_table);

        credit->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(credit);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 642, 24));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QString::fromUtf8("menuMode"));
        credit->setMenuBar(menuBar);

        menuBar->addAction(menuMode->menuAction());
        menuMode->addAction(actionCalc);
        menuMode->addAction(actionDeposit);

        retranslateUi(credit);

        QMetaObject::connectSlotsByName(credit);
    } // setupUi

    void retranslateUi(QMainWindow *credit)
    {
        credit->setWindowTitle(QCoreApplication::translate("credit", "Credit calculator", nullptr));
        actionCalc->setText(QCoreApplication::translate("credit", "Calc", nullptr));
        actionDeposit->setText(QCoreApplication::translate("credit", "Deposit", nullptr));
        sum_label->setText(QCoreApplication::translate("credit", "Sum", nullptr));
        rate_label->setText(QCoreApplication::translate("credit", "Rate(%)", nullptr));
        term_label->setText(QCoreApplication::translate("credit", "Term", nullptr));
        type_label->setText(QCoreApplication::translate("credit", "Type", nullptr));
        rate_type_label->setText(QCoreApplication::translate("credit", "Rate type", nullptr));
        term_type_label->setText(QCoreApplication::translate("credit", "Term type", nullptr));
        type_input->setItemText(0, QCoreApplication::translate("credit", "Annuity", nullptr));
        type_input->setItemText(1, QCoreApplication::translate("credit", "Differentiated", nullptr));

        rate_type_input->setItemText(0, QCoreApplication::translate("credit", "Per annum", nullptr));
        rate_type_input->setItemText(1, QCoreApplication::translate("credit", "Monthly", nullptr));

        term_type_input->setItemText(0, QCoreApplication::translate("credit", "Months", nullptr));
        term_type_input->setItemText(1, QCoreApplication::translate("credit", "Years", nullptr));

        calculate->setText(QCoreApplication::translate("credit", "Calculate", nullptr));
        clear->setText(QCoreApplication::translate("credit", "Clear", nullptr));
        menuMode->setTitle(QCoreApplication::translate("credit", "Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class credit: public Ui_credit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDIT_H
