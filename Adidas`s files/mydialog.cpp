#include "mydialog.h"
#include <QtWidgets>
#include <cstring>

using namespace std;

CustomPlainText::CustomPlainText(QWidget *parent): QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));

    updateLineNumberAreaWidth();
    highlightCurrentLine();
}

void CustomPlainText::CustomSetViewportMargins(int left, int top, int right, int bottom)
{
    setViewportMargins(left, top, right, bottom);
}

void CustomPlainText::CustomSetViewportMargins(const QMargins & margins)
{
    setViewportMargins(margins);
}

MyDialog::MyDialog(QWidget *parent) : QDialog (parent)
{

    setupUi(this);
}


void MyDialog::on_Start_clicked()
{
    string code;
    string memory;
    size_t dlina_stroki;
    QFile file("text.txt");
    QTextStream writeStream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QString temp = Input->text();
    Output->setText(temp);

    QString to_file = plainTextEdit->toPlainText();
    QStringList strList = to_file.split(QRegExp("[\n]"), QString::SkipEmptyParts);

    char **MassivChar = new char *[strList.size()];
    for(int i = 0; strList.at(i) != strList.last(); i++)
    {
        memory = strList.at(i).toStdString();
        dlina_stroki = memory.length();
        MassivChar[i] = new char[dlina_stroki];
        strcpy(MassivChar[i], memory.c_str());
    }

    EndlessTape A;
    A = temp.toStdString().c_str();


    Program B;

    B.InitProgram( MassivChar ,strList.size());
    B.Execute(A);
    const char * CurrentBukva = A.GetCurrentSymbol();
    temp = B.GetError();
    temp.prepend(*CurrentBukva);

    writeStream << to_file << endl;
    file.close();

    Output->setText(temp);


    delete []MassivChar;
}

int CustomPlainText::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, 1000);
    while (max >= 10) {
        max /= 10;
        digits++;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CustomPlainText::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CustomPlainText::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void CustomPlainText::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));

}

void CustomPlainText::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);

        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CustomPlainText::highlightErrorLine(int line)
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::red).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor.movePosition(QTextCursor::StartOfWord);
        selection.cursor.setPosition(line);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CustomPlainText::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}




