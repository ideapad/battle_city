#include "factory.h"

Factory::~Factory()
{

}

GameObject* PlayerFactory::createObject()
{
    return new Player;
}

GameObject* EnemyFactory::createObject()
{
    return new Enemy;
}

GameObject* BlockFactory::createObject()
{
    return new Block;
}

GameObject* BulletFactory::createObject(QPoint point, int dirRight, int dirUp)
{
    return new Bullet(point,dirRight,dirUp);
}

GameObject* TextFactory::createObject(int wight, int height)
{
    return new Text(wight,height);
}

GameObject* AnimationFactory::createObject(QRect position, const QString &image, const int imageCount)
{
    return new Animation(position,image,imageCount);
}
