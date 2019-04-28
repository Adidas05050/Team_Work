#ifndef MYDIALOG_H
#define MYDIALOG_H

#include "customplaintext.h"
#include "ui_mydialog.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRegExp>
#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QTextBlock>
#include <QList>
#include <QAbstractScrollArea>

class MyDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);

private:
    QWidget *lineNumberArea;

private slots:
    void on_pushButton_2_clicked();

};



#endif // MYDIALOG_H
