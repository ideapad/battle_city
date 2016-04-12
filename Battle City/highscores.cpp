#include <QTextStream>

#include "highscores.h"
#include "game.h"
#include "menu.h"


Highscores::Highscores()
{
    text_factory =  new TextFactory;
    block_factory = new BlockFactory;

    int i = 0;

    GameObject* Table = block_factory->createObject();
    Table->setDescription(QRect(0,0,800,600),":/images/Highscores.jpg");

    table.append(Table);


    QFile inputFile("C:\\Users\\Viktor\\Desktop\\NIGHT_WORK\\GAME_STATE\\Highscores.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line1 = in.readLine();
          QString line2 = in.readLine();

          GameObject* name = text_factory->createObject(800,400);
          GameObject* score = text_factory->createObject(800,400);
          name->setText(line1,QRect(100,135+i*50,0,0),"white");
          score->setText(line2,QRect(570,135+i*50,0,0),"white");

          table.append(name);
          table.append(score);
          i++;
       }
       inputFile.close();
    }


}

void Highscores::clearList()
{

}


void Highscores::draw()
{


}

QVector<GameObject *> Highscores::objects()
{
    QVector <GameObject*> objects;

    foreach (GameObject* fromstr, table)
    {
        objects.append(fromstr);
    }

    return objects;

}

void Highscores::mouse(GameWidget*, QMouseEvent*)
{

}

void Highscores::keyPress(QKeyEvent* event)
{
    switch(event->key()){
        case Qt::Key_Escape :
            Game::Instance().setCurrent(Menu::Instance());
            delete this;
            break;
    }


}

Highscores::~Highscores()
{
   qDeleteAll(table);
   table.clear();
   delete text_factory;
   delete block_factory;

}

void Highscores::keyRelease(GameWidget*, QKeyEvent*, QTimer*)
{

}

