#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent) : QDialog (parent)
{
    setupUi(this);
}

void MyDialog::on_pushButton_2_clicked()
{
    QFile file("text.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text );
    QString temp = lineEdit_2->text();
    QString to_file = plainTextEdit->toPlainText();
    QStringList strList = to_file.split(QRegExp("[\n]"), QString::SkipEmptyParts);

    lineEdit->setText(temp);
    QTextStream writeStream(&file);

    writeStream << to_file << endl;
    file.close();
}
