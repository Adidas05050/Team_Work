#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent) : QDialog (parent)
{
    setupUi(this);
}

void MyDialog::on_pushButton_2_clicked()
{
    QFile file("text.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text );

    QString temp = plainTextEdit->toPlainText();
    QStringList strList = temp.split(QRegExp("[\n]"), QString::SkipEmptyParts);

    QTextStream writeStream(&file);

    writeStream << temp << endl;
    file.close();
}
