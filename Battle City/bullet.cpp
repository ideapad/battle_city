#include "bullet.h"

Bullet::Bullet(QPoint point, int dirR, int dirU)
{
    Active = true;
    hitTarget = false;
    toDraw = true;

    image.load(":/images/images/bullet.png");

    size.setRect(point.x(),point.y(),5,5);

    dirRight = dirR;
    dirUp = dirU;

    connect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(updatePos()));
}

Bullet::~Bullet()
{
    disconnect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(updatePos()));
}

void Bullet::setDescription(QRect rect, QString string)
{
    size = rect;
    image.load(string);
}

void Bullet::setDirection(int x, int y)
{
    dirRight = x;
    dirUp = y;
}

bool Bullet::isActive()
{
    return Active;
}

void Bullet::setActive(bool a)
{
    Active = a;
}

void Bullet::setX(int a)
{
    size.setCoords(a,size.y(),10,10);
}

void Bullet::setY(int a)
{
    size.setCoords(size.x(),a,10,10);
}

int Bullet::getX()
{
    return size.x();
}

int Bullet::getY()
{
    return size.y();
}

void Bullet::updatePos()
{
    if ( size.x() >140 && size.x() < 655 && size.y() > 40 && size.y() < 555 ){
    size.translate(4*dirRight,4*dirUp);
    hitTarget = false;
    }else{
        this->setDescription(QRect(0,0,0,0),"");
        hitTarget = true;
    }
}

bool Bullet::hit()
{
    return hitTarget;
}

void Bullet::hited(bool ishitted)
{
    hitTarget = ishitted;
}

QRect Bullet::pos()
{
    return size;
}

QPixmap Bullet::img()
{
    return image;
}

