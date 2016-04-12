#include <QMessageBox>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QtMultimedia/QSound>
#include "loading.h"
#include "game.h"
#include "menu.h"

Loading* Loading::_instance = 0;

Loading* Loading::Instance()
{
    if(_instance == 0){
    _instance = new Loading;
    }
    return _instance;
}

Loading::Loading()
{
    block_factory = new BlockFactory;
    load = block_factory->createObject();
    load->setDescription(QRect(300,300,200,200),":/images/logo.png");
    pauser = 0;
    //QSound::play(":/sound/sounds/1.wav");
}

void Loading::clearList()
{

}


void Loading::draw()
{


}

QVector<GameObject *> Loading::objects()
{
    QVector <GameObject*> objects;

    int height = Game::Instance().WinGame->height();

    objects.reserve(1);

    if(pauser < height - 100 )
    {
        load->setDescription(QRect(100,height - pauser,600,189),":/images/logo.png");
    }else{
    Game::Instance().setCurrent(Menu::Instance());
    }
    ++pauser;

    objects.append(load);

    return objects;

}

void Loading::mouse(GameWidget*, QMouseEvent*)
{

}

void Loading::keyPress(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Return)
    {
        Game::Instance().setCurrent(Menu::Instance());
    }
}
void Loading::keyRelease(GameWidget*, QKeyEvent*, QTimer*)
{

}
