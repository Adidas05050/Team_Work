#include <QtTest>
#include <QtGui>
#include "test_qlineedit.h"
#include <QLineEdit>

void Test_QLineEdit::edit()
{
    QLineEdit a;
    QTest::keyClicks(&a, "abCDEf123-");

    QCOMPARE(a.text(), QString("abCDEf123-"));
    QVERIFY(a.isModified());
}
