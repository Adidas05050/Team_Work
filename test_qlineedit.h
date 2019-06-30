#ifndef TEST_QLINEEDIT_H
#define TEST_QLINEEDIT_H

#include <QObject>

class Test_QLineEdit : public QObject
{
    Q_OBJECT
private slots: // должны быть приватными
    void edit();

};

#endif // TEST_QLINEEDIT_H
