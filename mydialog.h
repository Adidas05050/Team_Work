#ifndef MYDIALOG_H
#define MYDIALOG_H

#include "ui_mydialog.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRegExp>

class MyDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
private slots:
    void on_pushButton_2_clicked();
};

#endif // MYDIALOG_H
