#include "gameobj.h"
#include "game.h"

// Abstract class GameObject  //

GameObject::~GameObject()
{

}

QPixmap GameObject::img()
{}

QRect GameObject::pos()
{}

void GameObject::setText(QString,QRect,QString)
{}

GameObject *GameObject::bulletPointer()
{}

void GameObject::move()
{}

void GameObject::fire()
{}

void GameObject::setDescription(QRect, QString)
{}

void GameObject::moveUp()
{}
void GameObject::moveDown()
{}
void GameObject::moveLeft()
{}
void GameObject::moveRight()
{}

void GameObject::setX(int)
{}

void GameObject::setY(int)
{}

int GameObject::getX()
{}

int GameObject::getY()
{}

int GameObject::getLifes()
{}

int GameObject::getID()
{}

bool GameObject::isActive()
{}

int GameObject::getType()
{}

void GameObject::setType(QPoint, int)
{}

void GameObject::setActive(bool)
{}

void GameObject::drawText(QString)
{}

bool GameObject::isDead()
{}

void GameObject::setID(int)
{}

void GameObject::setColliding(QVector<GameObject*>)
{}

void GameObject::die()
{}

void GameObject::setDirection(int, int)
{}


bool GameObject::hit()
{}


void GameObject::hited(bool)
{}

/////////////////////////////////////////////////


//////////// Player class ////////////////////////




////////////////// Enemy class //////////////////////////




//////////////////////////////////////////////////////////////


///////////////////////////// Block class ////////////////////


///////////////////////////////////////////////////////////////////

////////////////////// Bullet class ///////////////////////////////



//////////////////// Text class /////////////////



/////////// Animation ////////////////////



