#ifndef CUSTOMPLAINTEXT_H
#define CUSTOMPLAINTEXT_H

#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class CustomPlainText:public QPlainTextEdit
{
    Q_OBJECT
public:
    CustomPlainText(QWidget * parent = nullptr);
    void CustomSetViewportMargins(int left, int top, int right, int bottom);
    void CustomSetViewportMargins(const QMargins & margins);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

private:
    QWidget *lineNumberArea;

private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void updateLineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CustomPlainText *dialog) : QWidget(dialog) {
        myDialog = dialog;
    }

    QSize sizeHint() const override {
        return QSize(myDialog->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        myDialog->lineNumberAreaPaintEvent(event);
    }

private:
    CustomPlainText *myDialog;

};
#endif // CUSTOMPLAINTEXT_H
