#include "block.h"

Block::Block()
{
    Active = true;
    image.load(":/images/images/bricks.png");
    size.setRect(350,400,30,30);
}

Block::~Block()
{

}

QRect Block::pos()
{
    return size;
}

int Block::getX()
{
    return size.x();
}

int Block::getY()
{
    return size.y();
}

int Block::getID()
{
    return ID;
}

void Block::setID(int id)
{
    ID = id;
}

void Block::setX(int a)
{
    size.setCoords(a,size.y(),30,30);
}

void Block::setY(int a)
{
    size.setCoords(size.x(),a,30,30);
}

bool Block::isActive()
{
    return Active;
}

void Block::setActive(bool a)
{
    Active = a;
}

QPixmap Block::img()
{
    return image;
}



void Block::setDescription(QRect rect,QString string)
{
    size = rect;
    image.load(string);
}

