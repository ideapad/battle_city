#include "menu.h"
#include "about.h"
#include "game.h"
#include "gamestate.h"
#include "highscores.h"

#include "multiplayer.h"
#include <QDebug>


Menu::Menu()
{
    block_factory = new BlockFactory;
    text_factory = new TextFactory;

    logo = block_factory->createObject();
    items = block_factory->createObject();
    pointer = block_factory->createObject();

    logo->setDescription(QRect(100,100,600,189),":/images/logo.png");
    items->setDescription(QRect(302,400,196,102),":/images/menu.png");
    pointer->setDescription(QRect(265,403,18,18),":/images/images/PlayerRight.png");

    MenuItem = 1;
}

Menu* Menu::_instance = 0;

Menu* Menu::Instance()
{
    if( _instance == 0)
    {
        _instance = new Menu;
    }
    return _instance;
}

void Menu::clearList()
{
    qDeleteAll(Game::Instance().current->objects());
}

void Menu::draw()
{

}

QVector<GameObject *> Menu::objects()
{
    QVector <GameObject*> objects;

    objects.reserve(3);

    objects.append(logo);
    objects.append(items);
    objects.append(pointer);


    switch(MenuItem)
    {
   case 1:
        pointer->setDescription(QRect(265,395,19,19),":/images/images/PlayerRight.png");
        break;
   case 2:
        pointer->setDescription(QRect(265,420,19,19),":/images/images/PlayerRight.png");
        break;
   case 3:
        pointer->setDescription(QRect(265,445,19,19),":/images/images/PlayerRight.png");
        break;
   case 4:
        pointer->setDescription(QRect(265,467,19,19),":/images/images/PlayerRight.png");
        break;
   case 5:
        pointer->setDescription(QRect(265,490,19,19),":/images/images/PlayerRight.png");
        break;
    }

    return objects;

}

void Menu::mouse(GameWidget*, QMouseEvent*)
{

}

void Menu::keyPress(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
       {
               switch (MenuItem)
               {
               case 1:
                   MenuItem = 5;
                   break;
               case 2:
                   MenuItem = 1;
                   break;
               case 3:
                   MenuItem = 2;
                   break;
               case 4:
                   MenuItem = 3;
                   break;
               case 5:
                   MenuItem = 4;
                   break;
               }
        }

       if(event->key() == Qt::Key_Down)
        {
               switch (MenuItem)
               {
               case 1:
                  MenuItem = 2;
                  break;

               case 2:
                  MenuItem = 3;
                   break;

               case 3:
                  MenuItem = 4;
                   break;
               case 4:
                  MenuItem = 5;
                   break;
               case 5:
                  MenuItem = 1;
                   break;
                       }
         }

       if(event->key() == Qt::Key_Return)
        {
            switch (MenuItem) {
            case 1:
                Game::Instance().setCurrent(new GameState());
                break;
            case 2:
                Game::Instance().setCurrent(new Multiplayer());
                break;
            case 3:
                Game::Instance().setCurrent(new Highscores);
                break;
            case 4:
                Game::Instance().setCurrent(About::Instance());
                break;
            case 5:
                Game::Instance().WinGame->close();
                break;

            }
        }
}

void Menu::keyRelease(GameWidget*, QKeyEvent*, QTimer*)
{

}


