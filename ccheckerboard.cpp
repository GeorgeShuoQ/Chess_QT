#include "ccheckerboard.h"
#include <iostream>
#include<QPixmap>
Ccheckerboard::Ccheckerboard(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("国际象棋主界面");
    this->setWindowIcon(QPixmap(":/pics/piece_1.jpg"));
    this->setAutoFillBackground(true);
    pixmap = QPixmap(":/pics/fboard.png");
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    setPalette(palette);
    memset(Area,0,sizeof(Area));
    for(int c=0;c<=1;++c){
        for(int n=0;n<16;++n){
            switch(n){
            case 0:
                pieces[c*16+n]=new Crook(c,16*c,this);break;
            case 1:
                pieces[c*16+n]=new Cknight(c,16*c+1,this);break;
            case 2:
                pieces[c*16+n]=new Cbishop(c,16*c+2,this);break;
            case 3:
                pieces[c*16+n]=new Cqueen(c,16*c+3,this);break;
            case 4:
                pieces[c*16+n]=new Cking(c,this);break;
            case 5:
                pieces[c*16+n]=new Cbishop(c,16*c+5,this);break;
            case 6:
                pieces[c*16+n]=new Cknight(c,16*c+6,this);break;
            case 7:
                pieces[c*16+n]=new Crook(c,16*c+7,this);break;
            default:
                pieces[c*16+n]=new Cpawn(c,n%8,this);break;
            }
            pieces[c*16+n]->setParent(this);
            QObject::connect(pieces[c*16+n],&QPushButton::clicked,pieces[c*16+n],&Cpiece::clicked);
        }
    }

    Restart = new QPushButton(this);
    Restart->setText("复位");
    Restart->setFixedSize(80,80);
    Restart->setFont(QFont("楷体", 30));
    Restart->setFlat(true);
    Restart->move(80*9,0);
    QObject::connect(Restart,&QPushButton::clicked,this,&Ccheckerboard::renew);

    Saving = new QPushButton(this);
    Saving->setText("存档");
    Saving->setFixedSize(80,80);
    Saving->setFont(QFont("楷体", 30));
    Saving->setFlat(true);
    Saving->move(80*9,80*2);
    QObject::connect(Saving,&QPushButton::clicked,this,&Ccheckerboard::saveArchive);

    TIE = new QPushButton(this);
    TIE->setText("和局");
    TIE->setFixedSize(80,80);
    TIE->setFont(QFont("楷体", 30));
    TIE->setFlat(true);
    TIE->move(80*9,80*4);
    QObject::connect(TIE,&QPushButton::clicked,this,&Ccheckerboard::agreeToTie);

    Exit = new QPushButton(this);
    Exit->setText("退出");
    Exit->setFixedSize(80,80);
    Exit->setFont(QFont("楷体", 30));
    Exit->setFlat(true);
    Exit->move(80*9,80*6);
    QObject::connect(Exit,&QPushButton::clicked,this,&Ccheckerboard::close);

    this->setMaximumSize(pixmap.width()+80,pixmap.height());
    this->setMinimumSize(pixmap.width()+80,pixmap.height());

    selectedPiece=-1;
    movingColor=0;
    memset(moveArea,0,sizeof(moveArea));
}

void Ccheckerboard::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }
    QPoint pt = ev->pos(); //获得点击的点的坐标
    click(pt);
}

void Ccheckerboard::click(QPoint pt)
{
    if(selectedPiece==-1) return;
    if(moveArea[(pt.x()/80*80)/80][(pt.y()/80*80)/80]&&(selectedPiece==4||selectedPiece==20)&&pieces[selectedPiece]->moved==0){
                        if(selectedPiece==4){
                            if((pt.x()/80*80)/80==2){
                                Area[0][0][7] = false;
                                Area[0][4][7] = false;
                                Area[0][2][7] = true;
                                Area[0][3][7] = true;
                                pieces[4]->move(160,560);
                                pieces[0]->move(240,560);
                                pieces[4]->moved = 1;
                                pieces[0]->moved = 1;
                                movingfinished();
                                return;
                             }
                            else if((pt.x()/80*80)/80==6){
                                Area[0][7][7] = false;
                                Area[0][4][7] = false;
                                Area[0][5][7] = true;
                                Area[0][6][7] = true;
                                pieces[4]->move(480,560);
                                pieces[7]->move(400,560);
                                pieces[4]->moved = 1;
                                pieces[7]->moved = 1;
                                movingfinished();
                                return;
                            }
                        }
                        else if(selectedPiece==20){
                            if((pt.x()/80*80)/80==1){
                                Area[1][0][0] = false;
                                Area[1][3][0] = false;
                                Area[1][1][0] = true;
                                Area[1][2][0] = true;
                                pieces[20]->move(80, 0);
                                pieces[23]->move(160, 0);
                                pieces[20]->moved = 1;
                                pieces[23]->moved = 1;
                                movingfinished();
                                return;
                            }
                            if((pt.x()/80*80)/80==5){
                                Area[1][7][0] = false;
                                Area[1][3][0] = false;
                                Area[1][4][0] = true;
                                Area[1][5][0] = true;
                                pieces[20]->move(400, 0);
                                pieces[16]->move(320, 0);
                                pieces[20]->moved = 1;
                                pieces[16]->moved = 1;
                                movingfinished();
                                return;
                            }
                        }
    }
    int x = (pt.x()/80*80)/80, y = (pt.y()/80*80)/80;
    int xx = (pieces[selectedPiece]->x()/80*80)/80, yy = (pieces[selectedPiece]->y()/80*80)/80;
    if(moveArea[(pt.x()/80*80)/80][(pt.y()/80*80)/80]&&(selectedPiece>=8&&selectedPiece<=15)&&(yy == 3)){
        if(x == xx-1 && y == 2){
            Area[0][x][y] = true;
            Area[0][xx][yy] = false;
            Area[1][x][yy] = false;
            pieces[selectedPiece]->move(80*x, 160);
            pieces[selectedPiece]->moved++;
            pieces[31-x]->remove();
            movingfinished();
            return;
        }
        if(x == xx+1 && y == 2){
            Area[0][x][y] = true;
            Area[0][xx][yy] = false;
            Area[1][x][yy] = false;
            pieces[selectedPiece]->move(80*x, 160);
            pieces[selectedPiece]->moved++;
            pieces[31-x]->remove();
            movingfinished();
            return;
        }
    }
    if(moveArea[(pt.x()/80*80)/80][(pt.y()/80*80)/80]&&(selectedPiece>=24&&selectedPiece<=31)&&(yy == 4)){
        if(x == xx-1 && y == 5){
            Area[1][x][y] = true;
            Area[1][xx][yy] = false;
            Area[0][x][y-1] = false;
            pieces[selectedPiece]->move(80*x, 400);
            pieces[selectedPiece]->moved++;
            pieces[x+8]->remove();
            movingfinished();
            return;
        }
        if(x == xx+1 && y == 5){
            Area[1][x][y] = true;
            Area[1][xx][yy] = false;
            Area[0][x][y-1] = false;
            pieces[selectedPiece]->move(80*x, 400);
            pieces[selectedPiece]->moved++;
            pieces[x+8]->remove();
            movingfinished();
            return;
        }
    }
    if(moveArea[(pt.x()/80*80)/80][(pt.y()/80*80)/80] == true){
        int cl = pieces[selectedPiece]->color;
        int x = pieces[selectedPiece]-> x();
        int y = pieces[selectedPiece]-> y();
        pieces[selectedPiece] -> moved++;
        Area[cl][x/80][y/80] = false;
        Area[cl][(pt.x()/80*80)/80][(pt.y()/80*80)/80] = true;
        pieces[selectedPiece]->move(pt.x()/80*80,pt.y()/80*80);
        movingfinished();
    }
    else selectedPiece = -1;
}


QPixmap Ccheckerboard::drawSign(QPixmap pix1, QPixmap pix2, int x, int y)
{
    //把pix2画在pix1上
    QPainter painter(&pix1);
    painter.drawPixmap(x,y,pix2.width(),pix2.height(),pix2);
    return pix1;
}

void Ccheckerboard::signMoveArea(){
    QPixmap signedPM = pixmap;
    QPixmap dotPM(pieces[selectedPiece]->color? ":/pics/f_bdot.png" : ":/pics/f_wdot.png");
    for(int i=0;i<8;++i) for(int j=0;j<8;++j){
        if(moveArea[i][j]) signedPM=drawSign(signedPM,dotPM,80*i,80*j);
    }
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(signedPM));
    this->setPalette(palette);
    update();
}

void Ccheckerboard::movingfinished(){
    movingColor = !movingColor;
    selectedPiece=-1;
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);
    check();
    update();
}

void Ccheckerboard::promote(int No,int k){
    qDebug()<<No<<k;
    int xx=pieces[No]->x(),yy=pieces[No]->y(),cc=pieces[No]->color;
    pieces[No]->deleteLater();
    switch(k){
    case 0:
        pieces[No]=new Cqueen(cc,No,this);break;
    case 1:
        pieces[No]=new Cbishop(cc,No,this);break;
    case 2:
        pieces[No]=new Cknight(cc,No,this);break;
    case 3:
        pieces[No]=new Crook(cc,No,this);break;
    }
    pieces[No]->setParent(this);
    pieces[No]->QPushButton::move(xx,yy);
    QObject::connect(pieces[No],&QPushButton::clicked,pieces[No],&Cpiece::clicked);
    pieces[No]->show();
    check();
}

void Ccheckerboard::check(){
    pieces[0] -> movingArea(1);
    for(int i=1;i<16;++i){
        if(pieces[i]->alive)
        pieces[i] -> movingArea(2);
    }
    if(moveArea[pieces[20]->x()/80][pieces[20]->y()/80]) {
        //black king is checked
        pieces[20]->setStyleSheet("background-color: rgb(255, 0, 0);");
        pieces[20]->setFlat(false);
    }
    else{
        pieces[20]->setStyleSheet("background-color: none;");
        pieces[20]->setFlat(true);
    }
    pieces[16] -> movingArea(1);
    for(int i=17;i<31;++i){
        if(pieces[i]->alive)
        pieces[i] -> movingArea(2);
    }
    if(moveArea[pieces[4]->x()/80][pieces[4]->y()/80]){
        //white king is checked
        pieces[4]->setStyleSheet("background-color: rgb(255, 0, 0);");
        pieces[4]->setFlat(false);
    }
    else{
        pieces[4]->setStyleSheet("background-color: none;");
        pieces[4]->setFlat(true);
    }
    memset(moveArea,0,sizeof(moveArea));
    }

void Ccheckerboard::renew(){
    for(int n=0;n<32;++n){
        pieces[n]->hide();pieces[n]->deleteLater();
    }
    memset(Area,0,sizeof(Area));
    for(int c=0;c<=1;++c){
        for(int n=0;n<16;++n){
            switch(n){
            case 0:
                pieces[c*16+n]=new Crook(c,16*c,this);break;
            case 1:
                pieces[c*16+n]=new Cknight(c,16*c+1,this);break;
            case 2:
                pieces[c*16+n]=new Cbishop(c,16*c+2,this);break;
            case 3:
                pieces[c*16+n]=new Cqueen(c,16*c+3,this);break;
            case 4:
                pieces[c*16+n]=new Cking(c,this);break;
            case 5:
                pieces[c*16+n]=new Cbishop(c,16*c+5,this);break;
            case 6:
                pieces[c*16+n]=new Cknight(c,16*c+6,this);break;
            case 7:
                pieces[c*16+n]=new Crook(c,16*c+7,this);break;
            default:
                pieces[c*16+n]=new Cpawn(c,n%8,this);break;
            }
            pieces[c*16+n]->setParent(this);
            pieces[c*16+n]->show();
            QObject::connect(pieces[c*16+n],&QPushButton::clicked,pieces[c*16+n],&Cpiece::clicked);
        }
    }

    selectedPiece=-1;
    movingColor=0;
    memset(moveArea,0,sizeof(moveArea));
}

void Ccheckerboard::agreeToTie(){
    Game_Over_Dialog * gmd=new Game_Over_Dialog(this);
    gmd->tied();
}

void Ccheckerboard::saveArchive(){
    //保存为TXT文件
    bool exist;
    QString fileName;

    QDir *folder = new QDir;
    exist = folder->exists("D:/chess_archives");//查看目录是否存在

    if(!exist){//不存在就创建
        bool ok = folder->mkdir("D:/chess_archives");
        if(ok){
            QMessageBox::warning(this,tr("创建目录"),tr("创建成功!"));//添加提示方便查看是否成功创建
        }else{
            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
        }
    }
    fileName = "D:/chess_archives/archive_1.txt";

    QFile f(fileName);

    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){//覆盖写入
         QMessageBox::warning(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }
    else{
        char buffer[100];
        for(int i=0;i<32;++i){
            sprintf(buffer,"%d %d %d %d\n",i+1,pieces[i]->x(),pieces[i]->y(),pieces[i]->alive);
            f.write(buffer);
        }
    }
    QMessageBox::warning(this,tr("存档成功"),tr("存档至D:/chess_archives/archive_1.txt"));
    f.close();
}

void Ccheckerboard::loadArchive(){
    QString fileName = "D:/chess_archives/archive_1.txt";
    QFile f(fileName);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return ;
    }
    else{
        if(f.size() != 0){
            this->renew();
            QTextStream in(&f);
            int N,X,Y,A;
            while(!in.atEnd()){
                in>>N>>X>>Y>>A;
                if(N==0) break;
                if(A==1){
                    pieces[N-1]->move(X,Y);
                }
                else pieces[N-1]->remove();
            }
            this->show();
        }
    }
    f.close();
}
