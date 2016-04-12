#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QPainter>
#include <QRect>
#include "gamewidget.h"
#include "gameobj.h"
//#include "factory.h"

class Object
{
public:
    QRect size;
    QPixmap pixmap;

    Object(QRect rect, QString load)
    {
        size = rect;
        pixmap.load(load);
    }

    ~Object(){};
};

class State
{

public:
    virtual void clearList();
    virtual void draw(QPainter* painter);
    virtual QVector <GameObject*> objects();

    virtual void mouse(GameWidget*, QMouseEvent*) = 0;
    virtual void keyPress(QKeyEvent*) = 0;
    virtual void keyRelease(GameWidget*, QKeyEvent*, QTimer*) = 0;
};

#endif // STATE_H
