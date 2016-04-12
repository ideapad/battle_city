#ifndef ENEMY_H
#define ENEMY_H

#include "gameobj.h"
#include "game.h"

class Enemy : public QObject, public GameObject
{
    Q_OBJECT
public:
    void move();
  //  void fire();
    QRect pos();
    QPixmap img();
    void setX(int);
    void setY(int);
    void setColliding(QVector<GameObject*>);
    bool isActive();
    void setActive(bool);
    int getX();
    int getY();

    GameObject* bulletPointer();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();


    void setDescription(QRect,QString);
    Enemy();
    ~Enemy();

private:
    bool bulletHit;
    QVector<GameObject*> collideobjects;
    bool collision(QVector<GameObject*>);
    bool Active;
    bool shot;
    QTimer* timer;
    short int dirUp;
    short int dirRight;
    GameObject* bullet;
    QRect size;
    QPixmap image;

private slots:
    void moveEnemy();
    void changeDirection();
    void checkBullet();
    void fire();

};

#endif // ENEMY_H
