#include "game_over_dialog.h"
#include "ui_game_over_dialog.h"

Game_Over_Dialog::Game_Over_Dialog(Ccheckerboard * _pboard,QWidget *parent) :
    QDialog(parent),pboard(_pboard),
    ui(new Ui::Game_Over_Dialog)
{
    ui->setupUi(this);
}

Game_Over_Dialog::~Game_Over_Dialog()
{
    delete ui;
}

void Game_Over_Dialog::who_won(bool color){
    QLabel * label=new QLabel(this);
    this->setFixedSize(400,200);
    if(color) label->setText("白方获胜");
    else label->setText("黑方获胜");
    label->setStyleSheet("QLabel{font:30px;}");
    label->setFixedSize(200,30);
    label->setAlignment(Qt::AlignCenter);
    label->move(100,40);
    label->show();
    this->show();
}

void Game_Over_Dialog::tied(){
    QLabel * label=new QLabel(this);
    this->setFixedSize(400,200);
    label->setText("和棋");
    label->setStyleSheet("QLabel{font:30px;}");
    label->setFixedSize(200,30);
    label->setAlignment(Qt::AlignCenter);
    label->move(100,40);
    label->show();
    this->show();
}

void Game_Over_Dialog::on_pushButton_clicked()
{
    pboard->close();
    pboard->deleteLater();
    pboard=new Ccheckerboard;
    pboard->show();
    this->close();
}

void Game_Over_Dialog::on_pushButton_2_clicked()
{
    pboard->close();
    MainWindow * pmwin=new MainWindow;
    pmwin->show();
    this->close();
}
