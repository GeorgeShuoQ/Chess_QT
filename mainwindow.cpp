#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ccheckerboard.h"
#include "cpiece.h"
#include<QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkerboard = new Ccheckerboard;
    this->setWindowTitle("chess by 人类高质量小组");
    this->setFixedSize(588, 400);
    this->setWindowIcon(QPixmap(":/pics/piece_10"));
    connect(ui->startbtn, &QPushButton::clicked,[=](){
        this->hide();
        checkerboard->show();
    });
    connect(ui->exitbtn, &QPushButton::clicked,[=](){
        this->close();
    });
    ui->titlename->setStyleSheet("color:white;");
}

void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pics/bbk.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadbtn_clicked()
{
    checkerboard->loadArchive();this->hide();
}
