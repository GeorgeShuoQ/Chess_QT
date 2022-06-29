#ifndef CCHECKERBOARD_H
#define CCHECKERBOARD_H

#include <QWidget>
#include <cpiece.h>
#include <QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <cpromotion.h>

class Cpiece;
class Game_Over_Dialog;

class Ccheckerboard : public QWidget
{
    Q_OBJECT
public:
    Cpiece * pieces[32];
    bool moveArea[8][8];
    bool Area[2][8][8];//0没有 1白 2黑
    bool movingColor = 0;
    int selectedPiece;
    QPixmap pixmap;

    QPushButton * Restart;
    QPushButton * TIE;
    QPushButton * Saving;
    QPushButton * Exit;

    explicit Ccheckerboard(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *ev);
    void click(QPoint pt);

    QPixmap drawSign(QPixmap pix1, QPixmap pix2, int x, int y);
    void signMoveArea();
    void movingfinished();

    void promote(int No,int k);
    void check();

    void renew();
    void agreeToTie();
    void saveArchive();
    void loadArchive();
signals:

};

#endif // CCHECKERBOARD_H
