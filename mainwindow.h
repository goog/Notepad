#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCharFormat>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void keyPressEvent(QKeyEvent *);
    void formatOnWords(const QTextCharFormat &format);

private slots:

    void on_actionOpen_triggered();

    void on_actionSave_triggered();



    void on_btn_bold_clicked();

    void on_btn_italy_clicked();



    void on_btn_colors_clicked();

    void on_btn_clearfmt_clicked();

private:
    Ui::MainWindow *ui;

    int pressed_btn_type;
};

#endif // MAINWINDOW_H
