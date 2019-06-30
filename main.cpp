#include "mydialog.h"
#include <QtTest/QTest>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MyDialog *dialog = new MyDialog;
    dialog->show();
    QTest::qExec(new Test_QLineEdit, argc, argv);
    return app.exec();
}
