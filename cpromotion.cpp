#include "cpromotion.h"
#include "ui_cpromotion.h"

Cpromotion::Cpromotion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cpromotion)
{
    QPixmap backpic = QPixmap(":/pics/Promotion_background.png");
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(backpic));
    setPalette(palette);
    this->setMaximumSize(backpic.size());
    this->setMinimumSize(backpic.size());
    QPushButton * buttons[4];
    QString PicPaths[4]={":/pics/piece_8.png",":/pics/piece_9.png",":/pics/piece_10.png",":/pics/piece_11.png"};
    for(int i=0;i<4;++i){
        buttons[i]=new QPushButton(this);
        QPixmap pix;
        bool ret=pix.load(PicPaths[i]);
        if(!ret){
            qDebug()<<"图片加载失败";continue;
        }
        QSize picSize(30,30);
        pix=pix.scaled(picSize,Qt::KeepAspectRatio);
        buttons[i]->setFixedSize(30,30);
        buttons[i]->setFlat(true);
        buttons[i]->setAttribute(Qt::WA_TranslucentBackground);
        buttons[i]->setIcon(pix);
        buttons[i]->setIconSize(pix.size());
        buttons[i]->move(backpic.width()/8*(4+i),backpic.height()/3);
    }
    QObject::connect(buttons[0],&QPushButton::clicked,this,&Cpromotion::close_send_queen);
    QObject::connect(buttons[1],&QPushButton::clicked,this,&Cpromotion::close_send_bishop);
    QObject::connect(buttons[2],&QPushButton::clicked,this,&Cpromotion::close_send_knight);
    QObject::connect(buttons[3],&QPushButton::clicked,this,&Cpromotion::close_send_rook);
    ui->setupUi(this);
}

Cpromotion::~Cpromotion()
{
    delete ui;
}

void Cpromotion::close_send_queen(){
    emit sendsignal(0);
    this->close();
}
void Cpromotion::close_send_bishop(){
    emit sendsignal(1);
    this->close();
}
void Cpromotion::close_send_knight(){
    emit sendsignal(2);
    this->close();
}
void Cpromotion::close_send_rook(){
    emit sendsignal(3);
    this->close();
}
