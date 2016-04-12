#include "animation.h"

Animation::Animation(QRect position, const QString &image , const int imageCount)
{
    size = position;
    QImage img;
    img.load(image);
    int subImageHeight = img.height() / imageCount;

    for (int i=0;i< imageCount;i++)
    {
        QImage subImage = img.copy(0,i*subImageHeight,img.width(),subImageHeight);
        pixmaps.push_back(QPixmap::fromImage(subImage));
    }

    currentPixmap = 0;
    connect(&timer,SIGNAL(timeout()),SLOT(animate()));
    timer.start(70);
    animate();
}

Animation::~Animation()
{
    timer.stop();
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(animate()));
    pixmaps.clear();
}

void Animation::animate()
{
    if ( currentPixmap >= pixmaps.length())
    {
        IsAnimating = false;
        currentPixmap = 0;
    }

    image = pixmaps.at(currentPixmap);

    currentPixmap++;
}

QRect Animation::pos()
{
    return size;
}

QPixmap Animation::img()
{
    return image;
}

bool Animation::isActive()
{
    return IsAnimating;
}

