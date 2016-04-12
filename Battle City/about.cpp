#include "about.h"
#include "game.h"
#include "menu.h"

About::About()
{
    block_factory = new BlockFactory;

    logo = block_factory->createObject();
    logo->setDescription(QRect(0,0,800,600),":/images/About.jpg");

}

About* About::_instance = 0;

About* About::Instance()
{
    if( _instance == 0)
    {
        _instance = new About;
    }
    return _instance;
}

void About::clearList()
{
    qDeleteAll(Game::Instance().current->objects());
}

void About::draw()
{

}

QVector<GameObject *> About::objects()
{
    QVector <GameObject*> objects;

    objects.reserve(1);

    objects.append(logo);

    return objects;

}

void About::mouse(GameWidget*, QMouseEvent*)
{

}

void About::keyPress(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape :
        Game::Instance().setCurrent(Menu::Instance());
    }
}

void About::keyRelease(GameWidget*, QKeyEvent*, QTimer*)
{

}

