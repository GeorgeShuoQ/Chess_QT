#ifndef CPROMOTION_H
#define CPROMOTION_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Cpromotion;
}

class Cpromotion : public QWidget
{
    Q_OBJECT

public:
    explicit Cpromotion(QWidget *parent = nullptr);
    ~Cpromotion();
    void close_send_queen();
    void close_send_bishop();
    void close_send_knight();
    void close_send_rook();

private:
    Ui::Cpromotion *ui;

signals:
    void sendsignal(int);
};


#endif // CPROMOTION_H
