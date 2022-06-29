#ifndef GAME_OVER_DIALOG_H
#define GAME_OVER_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <ccheckerboard.h>
#include <mainwindow.h>

class Ccheckerboard;
class Cpiece;

namespace Ui {
class Game_Over_Dialog;
}

class Game_Over_Dialog : public QDialog
{
    Q_OBJECT

public:
    Ccheckerboard * pboard;
    explicit Game_Over_Dialog(Ccheckerboard * _pboard,QWidget *parent = nullptr);
    ~Game_Over_Dialog();
    void tied();

private:
    Ui::Game_Over_Dialog *ui;

private slots:
    void who_won(bool color);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // GAME_OVER_DIALOG_H
