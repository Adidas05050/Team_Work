/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "customplaintext.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *Close;
    CustomPlainText *plainTextEdit;
    QPushButton *Start;
    QLineEdit *Output;
    QLineEdit *Input;
    QPushButton *ErrorButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(581, 470);
        Close = new QPushButton(Dialog);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setGeometry(QRect(490, 270, 80, 21));
        plainTextEdit = new CustomPlainText(Dialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 80, 341, 371));
        Start = new QPushButton(Dialog);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(430, 80, 80, 21));
        Output = new QLineEdit(Dialog);
        Output->setObjectName(QString::fromUtf8("Output"));
        Output->setGeometry(QRect(30, 30, 531, 21));
        Output->setLayoutDirection(Qt::RightToLeft);
        Output->setAutoFillBackground(false);
        Output->setAlignment(Qt::AlignCenter);
        Output->setReadOnly(true);
        Output->setClearButtonEnabled(false);
        Input = new QLineEdit(Dialog);
        Input->setObjectName(QString::fromUtf8("Input"));
        Input->setGeometry(QRect(400, 120, 161, 21));
        ErrorButton = new QPushButton(Dialog);
        ErrorButton->setObjectName(QString::fromUtf8("ErrorButton"));
        ErrorButton->setGeometry(QRect(430, 370, 111, 81));

        retranslateUi(Dialog);
        QObject::connect(Close, SIGNAL(clicked()), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        Close->setText(QApplication::translate("Dialog", "Close", nullptr));
        Start->setText(QApplication::translate("Dialog", "\320\235\320\260\321\207\320\260\321\202\321\214", nullptr));
        Input->setText(QString());
        ErrorButton->setText(QApplication::translate("Dialog", "Error", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
