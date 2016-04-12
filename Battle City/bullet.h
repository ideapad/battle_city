#ifndef BULLET_H
#define BULLET_H

#include "bullet.h"
#include "game.h"

class Bullet : public QObject,public GameObject
{
    Q_OBJECT
public:
    bool Active;

    QRect pos();
    QPixmap img();
    void setX(int);
    void setY(int);
    bool isActive();
    void setActive(bool);
    int getX();
    int getY();
    void setDescription(QRect,QString);
    void setDirection(int,int);
    bool hit();
    void hited(bool);
    Bullet(QPoint,int,int);
    ~Bullet();
private:
    bool hitTarget;
    bool toDraw;
    int dirUp;
    int dirRight;
    QRect size;
    QPixmap image;

private slots:
    void updatePos();

};

#endif // BULLET_H
