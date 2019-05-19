#include "mydialog.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MyDialog *dialog = new MyDialog;
    dialog->show();
    return app.exec();
}
