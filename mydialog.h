#ifndef MYDIALOG_H
#define MYDIALOG_H

#include "customplaintext.h"
#include "ui_mydialog.h"
#include "EndlessTape.h"
#include "Program.h"
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
#include <fstream>
#include <cstring>

using namespace std;


class MyDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    void Proccess();

private:
    QWidget *lineNumberArea;
    CustomPlainText PlainText;

private slots:
    void on_Start_clicked();
    void on_FullSpeed_clicked();
    void on_Pause_clicked();
    void on_Reset_clicked();
    void on_Step_clicked();
};



#endif // MYDIALOG_H
