#ifndef CPIECE_H
#define CPIECE_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <game_over_dialog.h>
#include <qstring.h>
#include <ccheckerboard.h>

class Ccheckerboard;
class Game_Over_Dialog;

class Cpiece : public QPushButton
{
    Q_OBJECT
public:
    bool color;//0白色；1黑色
    int No;
    int pos_x,pos_y;
    //explicit Cpiece(QWidget *parent = nullptr);

    Ccheckerboard * pboard;
    QString normalPicPath;//正常贴图
    //void remove();

    Cpiece(int _color=0,int _No=0,QString _picpath="",Ccheckerboard * _pboard = nullptr,QWidget *parent = nullptr);
    void clicked(void);
    void selected(void);
    virtual void movingArea(int p)=0;
    virtual void move(int x,int y);
    virtual void remove();
    int moved;//sssss
    bool alive;

signals:
};

class Cking : public Cpiece
{
    Q_OBJECT
public:
    Cking(int _color=0,Ccheckerboard * _pboard = nullptr):
        Cpiece(_color,16*_color+4,_color?":/pics/piece_7.png":":/pics/piece_1.png",_pboard){}
    void movingArea(int p);
    void remove();

signals:
    void game_over_signal(bool);
};

class Cqueen : public Cpiece
{
public:
    Cqueen(int _color=0,int _No=0,Ccheckerboard * _pboard = nullptr):
        Cpiece(_color,_No,_color?":/pics/piece_8.png":":/pics/piece_2.png",_pboard){}
    void movingArea(int p);
};

class Cbishop : public Cpiece
{
public:
    Cbishop(int _color=0,int _No=0,Ccheckerboard * _pboard = nullptr):
        Cpiece(_color,_No,_color?":/pics/piece_9.png":":/pics/piece_3.png",_pboard){}
    void movingArea(int p);
};

class Cknight : public Cpiece
{
public:
    Cknight(int _color=0,int _No=0,Ccheckerboard * _pboard = nullptr):
        Cpiece(_color,_No,_color?":/pics/piece_10.png":":/pics/piece_4.png",_pboard){}
    void movingArea(int p);
};

class Crook : public Cpiece
{
public:
    Crook(int _color=0,int _No=0,Ccheckerboard * _pboard = nullptr):
        Cpiece(_color,_No,_color?":/pics/piece_11.png":":/pics/piece_5.png",_pboard){}
    void movingArea(int p);
};

class Cpawn : public Cpiece
{
    Q_OBJECT
public:
    Cpawn(int _color=0,int _No=0,Ccheckerboard * _pboard = nullptr):
        Cpiece(_color,16*_color+8+_No,_color?":/pics/piece_12.png":":/pics/piece_6.png",_pboard){}
    void movingArea(int p);
    void move(int x,int y);

private slots:
    void promote_to(int k);
};

#endif // CPIECE_H
