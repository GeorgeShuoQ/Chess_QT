#include "cpiece.h"

Cpiece::Cpiece(int _color,int _No,QString _picpath,Ccheckerboard * _pboard,QWidget *parent)
    : QPushButton{parent}
{
    normalPicPath=_picpath;color=_color;No=_No;
    moved=0;alive=true;
    pboard=_pboard;
    if(color==0) pos_x=(No%8)*80;
    else pos_x=(7-No%8)*80;
    if(No%16<8) pos_y=(7-7*color)*80;
    else pos_y=(6-5*color)*80;
    QPushButton::move(pos_x, pos_y);
    pboard -> Area[color][pos_x/80][pos_y/80] = true;//biaoji

    QPixmap pix;
    bool ret=pix.load(normalPicPath);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setFlat(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setIcon(pix);
    this->setIconSize(pix.size());
}

void Cpiece::clicked(){
    if(this->pboard!=NULL){
        int & se = pboard->selectedPiece;
        if(se==-1) selected();
        else{
                if(pboard->moveArea[this->x()/80][this->y()/80]){
                    pboard -> pieces[se] -> moved++;
                    pboard->Area[pboard->pieces[se]->color][pboard->pieces[se]->x()/80][pboard->pieces[se]->y()/80] = false;
                    pboard->Area[pboard->pieces[se]->color][this->x()/80][this->y()/80] = true;
                    pboard->Area[color][this->x()/80][this->y()/80] = false;
                    pboard->pieces[se]->move(this->x(),this->y());
                    this->remove();
                    pboard->movingfinished();
                    return;
                }
               else selected();
            }
        }
    }

void Cpiece::selected(){
    if(pboard!=NULL) if(alive) if(pboard->movingColor==color){
        pboard->selectedPiece = No;
        movingArea(1);
        pboard->signMoveArea();
    }
}

void Cpiece::remove(){
    this->alive=0;
    QPixmap pix;
    bool ret=pix.load(normalPicPath);
    if(!ret){
        qDebug()<<"图片加载失败";return;
    }
    QSize picSize(30,30);
    pix=pix.scaled(picSize,Qt::KeepAspectRatio);
    this->setFixedSize(pix.width(),pix.height());
    this->setFlat(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setIcon(pix);
    this->setIconSize(pix.size());
    this->move(80*8+40*color,100+30*(No%16));
}
void Cking::remove(){
    this->alive=0;
    this->move(80*8,color*560);
    Game_Over_Dialog * overDialog=new Game_Over_Dialog(pboard);
    connect(this,SIGNAL(game_over_signal(bool)),overDialog,SLOT(who_won(bool)));
    emit game_over_signal(color);
}

void Cpiece::move(int x,int y){
    QPushButton::move(x,y);
}
void Cpawn::move(int x,int y){
    QPushButton::move(x,y);
    if(y/80==7*(int)color){
        Cpromotion * promoting=new Cpromotion();
        promoting->show();
        connect(promoting,SIGNAL(sendsignal(int)),this,SLOT(promote_to(int)));
    }
}
void Cpawn::promote_to(int k){
    pboard->promote(No,k);
}

void Cking::movingArea(int p){
     if(p==1)
     memset(pboard->moveArea,0,sizeof(pboard->moveArea));
     int x = this->x()/80, y = this->y()/80;
     if(pboard->Area[color][x-1][y-1]!=true && x>0 && y>0) pboard->moveArea[x-1][y-1] = true;
     if(pboard->Area[color][x-1][y]!=true&&x>0) pboard->moveArea[x-1][y] = true;
     if(pboard->Area[color][x-1][y+1]!=true&&x>0&&y<7) pboard->moveArea[x-1][y+1] = true;
     if(pboard->Area[color][x][y+1]!=true&&y<7) pboard->moveArea[x][y+1] = true;
     if(pboard->Area[color][x+1][y+1]!=true&&x<7&&y<7) pboard->moveArea[x+1][y+1] = true;
     if(pboard->Area[color][x+1][y]!=true&&x<7) pboard->moveArea[x+1][y] = true;
     if(pboard->Area[color][x+1][y-1]!=true&&x<7&&y>0) pboard->moveArea[x+1][y-1] = true;
     if(pboard->Area[color][x][y-1]!=true&&y>0) pboard->moveArea[x][y-1] = true;
     if(moved==0){
         if(color == 0){
             if(pboard->Area[1][1][7]==false&&pboard->Area[1][2][7]==false&&pboard->Area[1][3][7]==false&&pboard->Area[color][1][7]==false&&pboard->Area[color][2][7]==false&&pboard->Area[color][3][7]==false&&pboard->pieces[0]->moved==0)
                 pboard->moveArea[2][7] = true;
             if(pboard->Area[1][5][7]==false&&pboard->Area[1][6][7]==false&&pboard->Area[color][5][7]==false&&pboard->Area[color][6][7]==false&&pboard->pieces[7]->moved==0)
                 pboard->moveArea[6][7] = true;
         }
         else {
             if(pboard->Area[0][1][0]==false&&pboard->Area[0][2][0]==false&&pboard->Area[color][1][0]==false&&pboard->Area[color][2][0]==false&&pboard->pieces[23]->moved==0)
                 pboard->moveArea[1][0] = true;
             if(pboard->Area[0][4][0]==false&&pboard->Area[0][5][0]==false&&pboard->Area[0][6][0]==false&&pboard->Area[color][4][0]==false&&pboard->Area[color][5][0]==false&&pboard->Area[color][6][0]==false&&pboard->pieces[16]->moved==0)
                 pboard->moveArea[5][0] = true;
         }
     }
}

void Cqueen::movingArea(int p){
    if(p==1)
    memset(pboard->moveArea,0,sizeof(pboard->moveArea));
    int x = this->x()/80, y = this->y()/80;
    int mn = x<=y? x:y;
    int xcolor;
    if(color==0) xcolor = 1;
    else xcolor = 0;
    for(int i=1;i<=mn; ++i){
        if(pboard->Area[color][x-i][y-i]==false&&pboard->Area[xcolor][x-i][y-i]==false){pboard->moveArea[x-i][y-i] = true; continue;}
        else if(pboard->Area[xcolor][x-i][y-i]==true){pboard->moveArea[x-i][y-i] = true; break;}
        else if(pboard->Area[color][x-i][y-i]==true){break;}
    }//zuoshangjiao

    int mx = x>=y? x:y;
    for(int i=1;i<=7-mx;++i){
        if(pboard->Area[color][x+i][y+i]==false&&pboard->Area[xcolor][x+i][y+i]==false){pboard->moveArea[x+i][y+i] = true; continue;}
        else if(pboard->Area[xcolor][x+i][y+i]==true){pboard->moveArea[x+i][y+i] = true; break;}
        else if(pboard->Area[color][x+i][y+i]==true) break;
    }//youxiajiao

    mn = x<=7-y? x:7-y;
    for(int i=1;i<=mn;++i){
        if(pboard->Area[color][x-i][y+i]==false&&pboard->Area[xcolor][x-i][y+i]==false){pboard->moveArea[x-i][y+i] = true; continue;}
        else if(pboard->Area[xcolor][x-i][y+i]==true){pboard->moveArea[x-i][y+i] = true; break;}
        else if(pboard->Area[color][x-i][y+i]==true){break;}
    }//zuoxiajiao

    mn = y<=7-x? y:7-x;
    for(int i=1;i<=mn;++i){
        if(pboard->Area[color][x+i][y-i]==false&&pboard->Area[xcolor][x+i][y-i]==false){pboard->moveArea[x+i][y-i] = true; continue;}
        else if(pboard->Area[xcolor][x+i][y-i]==true){pboard->moveArea[x+i][y-i] = true; break;}
        else if(pboard->Area[color][x+i][y-i]==true){break;}
    }//youshangjiao

    for(int i=1;i<=7-x;++i){
        if(pboard->Area[color][x+i][y]==false&&pboard->Area[xcolor][x+i][y]==false){pboard->moveArea[x+i][y] = true;continue;}
        if(pboard->Area[xcolor][x+i][y]==true){pboard->moveArea[x+i][y] = true; break;}
        if(pboard->Area[color][x+i][y]) break;
    }

    for(int i=1;i<=x;++i){
        if(pboard->Area[color][x-i][y]==false&&pboard->Area[xcolor][x-i][y]==false){pboard->moveArea[x-i][y] = true;continue;}
        if(pboard->Area[xcolor][x-i][y]==true){pboard->moveArea[x-i][y] = true; break;}
        if(pboard->Area[color][x-i][y]) break;
    }

    for(int i=1;i<=y;++i){
        if(pboard->Area[color][x][y-i]==false&&pboard->Area[xcolor][x][y-i]==false){pboard->moveArea[x][y-i] = true;continue;}
        if(pboard->Area[xcolor][x][y-i]==true){pboard->moveArea[x][y-i] = true; break;}
        if(pboard->Area[color][x][y-i]) break;
    }

    for(int i=1;i<=7-y;++i){
        if(pboard->Area[color][x][y+i]==false&&pboard->Area[xcolor][x][y+i]==false){pboard->moveArea[x][y+i] = true;continue;}
        if(pboard->Area[xcolor][x][y+i]==true){pboard->moveArea[x][y+i] = true; break;}
        if(pboard->Area[color][x][y+i]) break;
    }
}

void Cbishop::movingArea(int p){
    if(p == 1)
    memset(pboard->moveArea,0,sizeof(pboard->moveArea));
    int x = this->x()/80, y = this->y()/80;
    int mn = x<=y? x:y;
    int xcolor;
    if(color==0) xcolor = 1;
    else xcolor = 0;

    for(int i=1;i<=mn; ++i){
        if(pboard->Area[color][x-i][y-i]==false&&pboard->Area[xcolor][x-i][y-i]==false){pboard->moveArea[x-i][y-i] = true; continue;}
        else if(pboard->Area[xcolor][x-i][y-i]==true){pboard->moveArea[x-i][y-i] = true; break;}
        else if(pboard->Area[color][x-i][y-i]==true){break;}
    }//zuoshangjiao

    int mx = x>=y? x:y;
    for(int i=1;i<=7-mx;++i){
        if(pboard->Area[color][x+i][y+i]==false&&pboard->Area[xcolor][x+i][y+i]==false){pboard->moveArea[x+i][y+i] = true; continue;}
        else if(pboard->Area[xcolor][x+i][y+i]==true){pboard->moveArea[x+i][y+i] = true; break;}
        else if(pboard->Area[color][x+i][y+i]==true) break;
    }//youxiajiao

    mn = x<=7-y? x:7-y;
    for(int i=1;i<=mn;++i){
        if(pboard->Area[color][x-i][y+i]==false&&pboard->Area[xcolor][x-i][y+i]==false){pboard->moveArea[x-i][y+i] = true; continue;}
        else if(pboard->Area[xcolor][x-i][y+i]==true){pboard->moveArea[x-i][y+i] = true; break;}
        else if(pboard->Area[color][x-i][y+i]==true){break;}
    }//zuoxiajiao

    mn = y<=7-x? y:7-x;
    for(int i=1;i<=mn;++i){
        if(pboard->Area[color][x+i][y-i]==false&&pboard->Area[xcolor][x+i][y-i]==false){pboard->moveArea[x+i][y-i] = true; continue;}
        else if(pboard->Area[xcolor][x+i][y-i]==true){pboard->moveArea[x+i][y-i] = true; break;}
        else if(pboard->Area[color][x+i][y-i]==true){break;}
    }//youshangjiao
}

void Crook::movingArea(int p){
    if(p==1)
    memset(pboard->moveArea,0,sizeof(pboard->moveArea));
    int x = this->x()/80, y = this->y()/80;
    int xcolor;
    if(color==0) xcolor = 1;
    else xcolor = 0;
    for(int i=1;i<=7-x;++i){
        if(pboard->Area[color][x+i][y]==false&&pboard->Area[xcolor][x+i][y]==false){pboard->moveArea[x+i][y] = true;continue;}
        if(pboard->Area[xcolor][x+i][y]==true){pboard->moveArea[x+i][y] = true; break;}
        if(pboard->Area[color][x+i][y]) break;
    }

    for(int i=1;i<=x;++i){
        if(pboard->Area[color][x-i][y]==false&&pboard->Area[xcolor][x-i][y]==false){pboard->moveArea[x-i][y] = true;continue;}
        if(pboard->Area[xcolor][x-i][y]==true){pboard->moveArea[x-i][y] = true; break;}
        if(pboard->Area[color][x-i][y]) break;
    }

    for(int i=1;i<=y;++i){
        if(pboard->Area[color][x][y-i]==false&&pboard->Area[xcolor][x][y-i]==false){pboard->moveArea[x][y-i] = true;continue;}
        if(pboard->Area[xcolor][x][y-i]==true){pboard->moveArea[x][y-i] = true; break;}
        if(pboard->Area[color][x][y-i]) break;
    }

    for(int i=1;i<=7-y;++i){
        if(pboard->Area[color][x][y+i]==false&&pboard->Area[xcolor][x][y+i]==false){pboard->moveArea[x][y+i] = true;continue;}
        if(pboard->Area[xcolor][x][y+i]==true){pboard->moveArea[x][y+i] = true; break;}
        if(pboard->Area[color][x][y+i]) break;
    }
}

void Cknight::movingArea(int p){
    if(p==1)
    memset(pboard->moveArea,0,sizeof(pboard->moveArea));
    int x = this->x()/80, y = this->y()/80;
    if(pboard->Area[color][x-1][y-2]==false&&x>0&&y>1) pboard->moveArea[x-1][y-2] = true;
    if(pboard->Area[color][x+1][y-2]==false&&x<7&&y>1) pboard->moveArea[x+1][y-2] = true;
    if(pboard->Area[color][x-2][y-1]==false&&x>1&&y>0) pboard->moveArea[x-2][y-1] = true;
    if(pboard->Area[color][x-2][y+1]==false&&x>1&&y<7) pboard->moveArea[x-2][y+1] = true;
    if(pboard->Area[color][x-1][y+2]==false&&x>0&&y<6) pboard->moveArea[x-1][y+2] = true;
    if(pboard->Area[color][x+1][y+2]==false&&x<7&&y<6) pboard->moveArea[x+1][y+2] = true;
    if(pboard->Area[color][x+2][y-1]==false&&x<6&&y>0) pboard->moveArea[x+2][y-1] = true;
    if(pboard->Area[color][x+2][y+1]==false&&x<6&&y<7) pboard->moveArea[x+2][y+1] = true;
}

void Cpawn::movingArea(int p){
    if(p==1)
    memset(pboard->moveArea,0,sizeof(pboard->moveArea));
    int x = this->x()/80, y = this->y()/80;
    int xcolor;
    if(color==0) xcolor = 1;
    else xcolor = 0;

    if(x==pos_x/80&&y==pos_y/80){
        if(color == 0){
            if(pboard->Area[xcolor][x][y-1]==false&&pboard->Area[color][x][y-1]==false){
                pboard->moveArea[x][y-1] = true;
                if(pboard->Area[xcolor][x][y-2]==false&&pboard->Area[color][x][y-2]==false)
                    pboard->moveArea[x][y-2] = true;
            }
        }

        if(color == 1){
            if(pboard->Area[xcolor][x][y+1]==false&&pboard->Area[color][x][y+1]==false){
                pboard->moveArea[x][y+1] = true;
                if(pboard->Area[xcolor][x][y+2]==false&&pboard->Area[color][x][y+2]==false)
                    pboard->moveArea[x][y+2] = true;
            }
        }
    }

    else {
        if(color == 0)
            if(pboard->Area[xcolor][x][y-1]==false&&pboard->Area[color][x][y-1]==false){
                pboard->moveArea[x][y-1] = true;}
        if(color == 1)
            if(pboard->Area[xcolor][x][y+1]==false&&pboard->Area[color][x][y+1]==false){
                pboard->moveArea[x][y+1] = true;}
    }

    if(color == 0){
        if(pboard->Area[xcolor][x-1][y-1]==true) pboard->moveArea[x-1][y-1] = true;
        if(pboard->Area[xcolor][x+1][y-1]==true) pboard->moveArea[x+1][y-1] = true;
    }

    if(color == 1){
        if(pboard->Area[xcolor][x-1][y+1]==true) pboard->moveArea[x-1][y+1] = true;
        if(pboard->Area[xcolor][x+1][y+1]==true) pboard->moveArea[x+1][y+1] = true;
    }

    if(color == 0){
        if(y == 3 && x > 0 && pboard->Area[xcolor][x-1][2] == false&&pboard->Area[0][x-1][2] == false && pboard->Area[xcolor][x-1][3] == true && pboard->pieces[32-x]->moved == 1){
            pboard->moveArea[x-1][2] = true;
        }
        if(y == 3 && x < 7 && pboard->Area[xcolor][x+1][2] == false&&pboard->Area[0][x+1][2] == false && pboard->Area[xcolor][x+1][3] == true && pboard->pieces[30-x]->moved == 1){
            pboard->moveArea[x+1][2] = true;
        }
    }
    if(color == 1){
        if(y == 4 && x > 0 && pboard->Area[xcolor][x-1][5] == false&&pboard->Area[1][x-1][5] == false && pboard->Area[xcolor][x-1][4] == true && pboard->pieces[x+7]->moved == 1){
            pboard->moveArea[x-1][5] = true;
        }
        if(y == 4 && x < 7  && pboard->Area[xcolor][x+1][5] == false &&pboard->Area[1][x+1][5] == false && pboard->Area[xcolor][x+1][4] == true && pboard->pieces[x+9]->moved == 1){
            pboard->moveArea[x+1][5] = true;
        }
    }

}
