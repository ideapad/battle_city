#ifndef BLOCK_H
#define BLOCK_H

#include "gameobj.h"
#include "game.h"

class Block : public GameObject
{
public:
    bool Active;
    QRect pos();
    QPixmap img();
    bool isActive();
    void setActive(bool);
    int getID();
    void setID(int);
    int getX();
    int getY();
    void setX(int);
    void setY(int);
    void setDescription(QRect,QString);

    Block();
    ~Block();

private:

    int ID;
    QRect size;
    QPixmap image;

};

#endif // BLOCK_H
