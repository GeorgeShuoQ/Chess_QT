#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ccheckerboard.h>

class Ccheckerboard;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    Ccheckerboard * checkerboard;

private slots:
    void on_loadbtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
