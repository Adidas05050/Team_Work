# Shared files
SOURCES += my_dialog.cpp
FORMS += my_dialog.ui
HEADERS += my_dialog.h

# Unique files
SOURCES += test_qlineedit.cpp
HEADERS += test_qlineedit.h

# Qt
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# QTest
QT += testlib
