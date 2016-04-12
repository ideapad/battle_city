#include "player.h"
#include "bullet.h"
#include "game.h"

Player::Player()
{
    directionRight = 0;
    directionUp = -1;

    bulletHit = true;

    bullet = new Bullet(QPoint(this->getX()+15*directionRight,this->getY()+15*directionUp),directionRight,directionUp);

    connect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(checkBullet()));

    speed_x = 0;
    speed_y = 0;

    Lifes = 3;
    Notdead = true;

    player_type = 1;

    image.load(":/images/images/PlayerUp.png");
    size = QRect(320,530,30,30);
    connect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(updatePos()));
}

int Player::getLifes()
{
    return Lifes;
}

void Player::updatePos()
{
    bool collide = false;

    size.translate(speed_x,speed_y);

    foreach(GameObject* collision, collidings)
    {
      if ( this->pos().intersects(collision->pos()) || size.x()<140 || size.x()>630 || size.y()<40 || size.y()>530 )
      collide = true;
    }

    if (collide)
    size.translate(-speed_x,-speed_y);
}

int Player::getType()
{
    return player_type;
}

void Player::die()
{
    Lifes--;
    if ( Lifes !=0)
    {
        if(player_type == 1)
      size = QRect(320,530,30,30);
        else
      size = QRect(380,530,30,30);
    }else{
        disconnect(Game::Instance().WinGame->timer,SIGNAL(timeout()),this,SLOT(updatePos()));
    }
}

void Player::setType(QPoint pos, int type)
{
    size.setRect(pos.x(),pos.y(),30,30);
    player_type = type;

    if( type == 2)
    image.load(":/images/Player2Up.png");
}

GameObject* Player::bulletPointer()
{
    return bullet;
}

void Player::move()
{
    speed_x = 0;
    speed_y = 0;
}

void Player::setX(int a)
{
    size.setRect(a,size.y(),30,30);
}

void Player::setY(int a)
{
    size.setRect(size.x(),a,30,30);
}

int Player::getX()
{
    return size.x();
}

int Player::getY()
{
    return size.y();
}

bool Player::isDead()
{

}

QPixmap Player::img()
{
    return image;
}

QRect Player::pos()
{
    return size;
}

void Player::moveUp()
{
    if(player_type == 1)
   image.load(":/images/images/PlayerUp.png");
    else
   image.load(":/images/Player2Up.png");

   directionRight  = 0;
   directionUp = -1;

   speed_x = 0;
   speed_y = -2;

}

void Player::moveDown()
{
    if(player_type == 1)
   image.load(":/images/images/PlayerDown.png");
    else
   image.load(":/images/Player2Down.png");

    directionRight  = 0;
    directionUp = 1;

    speed_x = 0;
    speed_y = 2;
}

void Player::moveLeft()
{
    if(player_type == 1)
   image.load(":/images/images/PlayerLeft.png");
    else
   image.load(":/images/Player2Left.png");

    directionRight  = -1;
    directionUp = 0;

    speed_x = -2;
    speed_y = 0;
}

void Player::moveRight()
{
    if(player_type == 1)
   image.load(":/images/images/PlayerRight.png");
    else
   image.load(":/images/Player2Right.png");

    directionRight  = 1;
    directionUp = 0;

    speed_x = 2;
    speed_y = 0;
}

void Player::setColliding(QVector<GameObject *> vector)
{
    collidings = vector;
}

void Player::checkBullet()
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

void Player::fire()
{
    if(bulletHit)
    {
       delete bullet;
       bullet = new Bullet(QPoint(size.x()+12,size.y()+13),directionRight,directionUp);
       QSound::play(":/sound/shoot.wav");
    }
}

bool Player::isActive()
{
    return Notdead;
}
void Player::setActive(bool a)
{
    Notdead = a;
}

