#ifndef FACTORY_H
#define FACTORY_H

#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bullet.h"
#include "text.h"
#include "animation.h"

class Factory
{
public:
    virtual GameObject* createObject() = 0;
    virtual ~Factory();
};

class PlayerFactory : public Factory
{
public:
    GameObject* createObject();
};

class EnemyFactory : public Factory
{
public:
    GameObject* createObject();
};

class BlockFactory : public Factory
{
public:
    GameObject* createObject();
};

class BulletFactory : public Factory
{
public:
    GameObject* createObject(QPoint,int,int);
};

class TextFactory
{
public:
    GameObject* createObject(int,int);
};

class AnimationFactory
{
public:
    GameObject* createObject(QRect position, const QString &image, const int imageCount);
};


#endif // FACTORY_H
