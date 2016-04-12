#ifndef ANIMATION_H
#define ANIMATION_H

#include "gameobj.h"
#include "game.h"

class Animation : public QObject, public GameObject
{
  Q_OBJECT
public:
    Animation(QRect position, const QString &image, const int imageCount);
    ~Animation();

    QRect pos();
    QPixmap img();
    bool isActive();
private:
    bool IsAnimating;
    QList<QPixmap> pixmaps;
    QRect size;
    QPixmap image;
    int currentPixmap;
    QTimer timer;
public slots:
    void animate();

};

#endif // ANIMATION_H
