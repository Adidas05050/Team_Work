#include "mydialog.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MyDialog *dialog = new MyDialog;
    QTextEdit text;
    dialog->show();
    return app.exec();
}
