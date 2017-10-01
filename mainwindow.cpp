#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("My notebook"));
    pressed_btn_type = -1;

    ui->btn_bold->setStyleSheet("color: blue;"
                                "background-color: yellow");
    ui->btn_italy->setStyleSheet("color: blue;"
                                "background-color: yellow");
    ui->btn_colors->setStyleSheet("color: blue;"
                                "background-color: yellow");
    ui->btn_clearfmt->setStyleSheet("color: blue;"
                                "background-color: yellow");

    QPixmap pixmap;
    pixmap.load("://img/IMG_00.jpg");

    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);

    ui->textEdit->viewport()->setAutoFillBackground(false);
    ui->textEdit->setStyleSheet("font: 16pt");

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_quitBTN_clicked()
//{
//    QCoreApplication::quit();
//}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                  tr("Text Files (*.txt);;C++ Files (*.c *.cpp *.h)"));

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }

        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();

    }

}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                  tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            // error message
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toHtml();
            stream.flush();
            file.close();
        }
    }

}

void MainWindow::formatOnWords(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}



void MainWindow::on_btn_bold_clicked()
{
    static bool flag = true;
    QTextCharFormat fmt;

    if(flag == true)
    {
        fmt.setFontWeight(QFont::Bold);
        //pressed_btn_type = 1;
    }
    else
    {
        fmt.setFontWeight(QFont::Normal);    
    }

    formatOnWords(fmt);

    flag = !flag;
}

void MainWindow::on_btn_italy_clicked()
{
    static bool flag = true;
    QTextCharFormat fmt;

    if(flag == true)
        fmt.setFontItalic(true);
    else
        fmt.setFontItalic(false);

    formatOnWords(fmt);

    flag = !flag;
}


void MainWindow::on_btn_colors_clicked()
{
    QColor color = QColorDialog::getColor();
    if(!color.isValid())
        return;

    //QColor color = Qt::red;
    QTextCharFormat fmt;
    fmt.setForeground(color);

    formatOnWords(fmt);
}

//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    qDebug() << event->key();
//    if(event->key() == Qt::Key_Enter)
//    {

//    }

//}


//clear format
void MainWindow::on_btn_clearfmt_clicked()
{
    QTextCharFormat fmt;

    fmt.setFontWeight(QFont::Normal);
    fmt.setFontItalic(false);
    fmt.setForeground(Qt::black);

    formatOnWords(fmt);
}
