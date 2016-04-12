#ifndef TEXT_H
#define TEXT_H

#include "gameobj.h"
#include "game.h"

class Text : public GameObject
{
public:
    Text(int,int);
    void drawText(QString);
    void setText (QString,QRect,QString);
    QPixmap img();
    QRect pos();
private:
    QFont font;
    QPainter *p;
    QPixmap image;
    QRect size;
};

#endif // TEXT_H
