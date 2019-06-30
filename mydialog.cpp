#include "mydialog.h"
#include <QtWidgets>

int ActivFase = 0; // 0 - first, 1 - next, 2 - pause, 3 -step
bool b_FullSpeed = false;
bool b_Reset = false;
void MyDialog::Proccess()
{
    Start->setText("Продолжить");
    QFile file("text.txt");
    QTextStream writeStream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QString temp = Input->text();
    Output->setText(temp);
    Output->setSelection(0,1);
    QString to_file = plainTextEdit->toPlainText();
    QStringList strList = to_file.split(QRegExp("[\n]"));
    writeStream << to_file << endl;
    file.close();// first stade

    if(to_file.isEmpty())
    {
        ErrorLine->setText("Code is empty.");
        return;
    }
    string code;
    string memory;
    size_t dlina_stroki;

    int ListSize = strList.size();
    char **MassivChar = new char *[ListSize];
    for(int i = 0; i < ListSize; i++)
    {
        memory = strList.at(i).toStdString();
        dlina_stroki = memory.length();
        MassivChar[i] = new char[dlina_stroki + 1];
        strcpy(MassivChar[i], memory.c_str());
        MassivChar[i][dlina_stroki] = '\0';
    }
    //second stade
    int x = 0;
    EndlessTape Tape;
    Program program;
    const char * CurrentBukva;
    Output->setSelection(x,1);
    if(!program.InitProgram( MassivChar , ListSize ))
    {
        ErrorLine->setText(program.GetError());

        for(int i = 0; i < ListSize; i++)
            delete [] MassivChar[i];

        delete []MassivChar;

        return;
    }
    Tape = temp.toStdString().c_str();
    while(!program.IsHalted())
    {
        while(ActivFase == 2)
        {
            QEventLoop loop;
            QTimer timer;
            timer.setInterval(100);
            connect (&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
            timer.start();
            loop.exec();
            if(b_Reset)
                return;
        }
        if(!b_FullSpeed)
        {
            QEventLoop loop;
            QTimer timer;
            timer.setInterval(50);
            connect (&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
            timer.start();
            loop.exec();
        }
        if(b_Reset)
            return;
        CurrentBukva = Tape.GetCurrentSymbol();
        if(!program.Execute(Tape))
        {
            ErrorLine->setText(program.GetError());
            break;
        }
        if(x < 0)
        {
            temp.prepend(*CurrentBukva);
            x = 0;
        }
        else if(x > temp.size())
        {
            temp.append(*CurrentBukva);
        }
        else
            temp[x] = (*CurrentBukva);

        Output->setText(temp);
        Output->setSelection(x,1);
        x += Tape.GetLastShift();



        if(ActivFase == 3)
            ActivFase = 2;
    }
    if(program.IsHalted())
    {
        Pause->setEnabled(false);
        Start->setEnabled(false);
        Step->setEnabled(false);
    }
}

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
    Output->setEnabled(false);
    Output->setStyleSheet("QLineEdit { selection-background-color: rgb(150, 150, 00); }");
    Output->setSelection(0,1);
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

void MyDialog::on_Start_clicked()
{
    if(ActivFase == 0)
    {
        ActivFase = 3;
        Pause->setEnabled(true);
        b_Reset = false;
        Proccess();
    }
    else if(ActivFase == 2)
    {
        Start->setText("Начать");
        ActivFase = 1;
        Start->setEnabled(false);
        Pause->setEnabled(true);
    }
    else if(ActivFase == 3)
    {
        Start->setText("Начать");
        ActivFase = 1;
        Start->setEnabled(false);
        Pause->setEnabled(true);
    }
}

void MyDialog::on_FullSpeed_clicked()
{
    if(b_FullSpeed)
        b_FullSpeed = false;
    else
        b_FullSpeed = true;
}

void MyDialog::on_Pause_clicked()
{
    ActivFase = 2;
    Start->setText("Продолжить");
    Pause->setEnabled(false);
    Start->setEnabled(true);
    Step->setEnabled(true);
}

void MyDialog::on_Reset_clicked()
{
    QString temp = Input->text();
    Output->repaint();
    Output->setText(temp);
    ActivFase = 0;
    Start->setEnabled(true);
    Start->setText("Начать");
    Step->setEnabled(true);
    b_Reset = true;
    Output->setSelection(0,1);
    ErrorLine->clear();
}

void MyDialog::on_Step_clicked()
{
    Start->setText("Продолжить");
    Start->setEnabled(true);
    Pause->setEnabled(false);
    ActivFase = 3;
}
