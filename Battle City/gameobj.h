#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMessageBox>
#include <QMatrix>
#include <QObject>
//#include "game.h"
#include <QTimer>
#include <QSound>

class GameObject
{
public:
    virtual void move();
    virtual ~GameObject();
    virtual void setDescription(QRect,QString);
    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void setX(int);
    virtual void setY(int);

    virtual void drawText(QString);
    virtual void setText (QString,QRect,QString);

    virtual GameObject* bulletPointer();

    virtual int getLifes();

    virtual void setType(QPoint,int);
    virtual int getType();

    virtual int getID();
    virtual void setID(int);

    virtual void setColliding(QVector<GameObject*>);
    virtual bool isActive();
    virtual void setActive(bool);
    virtual bool hit();
    virtual void hited(bool);
    virtual bool isDead();
    virtual void die();
    virtual int getX();
    virtual int getY();
    virtual void setDirection(int,int);
    virtual void fire();
    virtual QRect pos();
    virtual QPixmap img();

};


#endif // GAMEOBJECT_H
