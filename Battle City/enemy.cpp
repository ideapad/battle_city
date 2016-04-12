#include "enemy.h"
#include "bullet.h"

Enemy::Enemy()
{
    bulletHit = true;

    bullet = new Bullet(QPoint(this->getX()+15*dirRight,this->getY()+15*dirUp),dirRight,dirUp);

    Active = true;
    shot = true;

    timer = new QTimer;
    dirRight = 0;
    dirUp = 1;
    size.setRect(630,40,30,30);
    image.load(":/images/images/EnemyDown.png");

    connect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(checkBullet()));
    connect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(moveEnemy()));
    connect(timer,SIGNAL(timeout()),this,SLOT(fire()));
    connect(timer,SIGNAL(timeout()),this,SLOT(changeDirection()));

    timer->start(600);
}

Enemy::~Enemy()
{
    disconnect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(checkBullet()));
    disconnect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(moveEnemy()));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(fire()));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(changeDirection()));

    delete timer;

    collideobjects.clear();
}



bool Enemy::isActive()
{
    return Active;
}

void Enemy::setActive(bool a)
{
    Active = a;
}

void Enemy::setColliding(QVector<GameObject*> a)
{
    collideobjects = a;
}

void Enemy::checkBullet()
{
    if(bullet!= nullptr)
    {
        if(bullet->hit())
        {
            bulletHit = true;
            delete bullet;
            bullet = nullptr;
        }else
        {
            bulletHit = false;
        }
    }
}

GameObject* Enemy::bulletPointer()
{
    return bullet;
}

void Enemy::changeDirection()
{
    int random = rand()%100;

        if(random <25)
            moveUp();
        if(random >25 && random < 50)
            moveDown();
        if(random >50 && random <75)
            moveLeft();
        if(random <100 && random >75)
            moveRight();

//        moveDown();
}

void Enemy::moveEnemy()
{
    bool collide = false;

    size.translate(dirRight,dirUp);

    foreach(GameObject* collision, collideobjects)
    {
      if ( this->pos().intersects(collision->pos()) || size.x()<140 || size.x()>630 || size.y()<40 || size.y()>530 )
      collide = true;
    }

    if (collide)
    size.translate(-dirRight,-dirUp);

}

void Enemy::setX(int a)
{
    size.setCoords(a,size.y(),30,30);
}

void Enemy::setY(int a)
{
    size.setCoords(size.x(),a,30,30);
}

int Enemy::getX()
{
    return size.x();
}

int Enemy::getY()
{
    return size.y();
}

QRect Enemy::pos()
{
    return size;
}

QPixmap Enemy::img()
{
    return image;
}

void Enemy::setDescription(QRect a, QString b)
{
    size = a;
    image.load(b);
}


void Enemy::moveDown()
{
    image.load(":/images/images/EnemyDown.png");

    dirUp = 1;
    dirRight = 0;

}

void Enemy::moveUp()
{
    image.load(":/images/images/EnemyUp.png");

    dirRight = 0;
    dirUp = -1;

}

void Enemy::moveLeft()
{
    image.load(":/images/images/EnemyLeft.png");

    dirRight = -1;
    dirUp = 0;

}

void Enemy::moveRight()
{
    image.load(":/images/images/EnemyRight.png");

    dirRight = 1;
    dirUp = 0;

}

void Enemy::move()
{

}

bool Enemy::collision(QVector<GameObject*> collisions)
{
    foreach (GameObject* colliding, collisions) {
        if(this->getX() > colliding->getX()   &&
           this->getX() < colliding->getX()+ colliding->pos().width() &&
           this->getY() > colliding->getY() &&
           this->getY() < colliding->getY()+ colliding->pos().height())
        {
            return true;
        }else{
            return false;
        }
    }
}

void Enemy::fire()
{
    if(bulletHit)
    {
       delete bullet;
       bullet = new Bullet(QPoint(size.x()+12,size.y()+13),dirRight,dirUp);
       QSound::play(":/sound/shoot.wav");
    }
}

