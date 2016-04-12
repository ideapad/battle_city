#include <QMessageBox>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QtMultimedia/QSound>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>

#include "highscores.h"
#include "game.h"
#include "menu.h"
#include "gamestate.h"


enum {Empty,Brick,Green,Water,Steel};

enum {Singleplayer,Multiplayer};

GameState::GameState()
{
    int gameMap[13][13]  = {{0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,0,0,0,1,4,4,4,0,0,0},
                            {0,0,0,0,0,2,1,2,3,3,0,0,0},
                            {0,0,0,1,1,1,1,1,1,1,0,0,0},
                            {0,0,0,0,0,2,1,2,3,3,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0},};


    Lose = false;



    player_factory    =    new PlayerFactory;
    enemy_factory     =    new EnemyFactory;
    block_factory     =    new BlockFactory;
    text_factory      =    new TextFactory;
    animation_factory =    new AnimationFactory;




    player1 = player_factory->createObject();


    playerlifes = block_factory->createObject();
    playerlifes->setDescription(QRect(680,380,40,40),":/images/player1.png");
    score = text_factory->createObject(110,100);
    score->setText("SCORE \n 0",QRect(680,220,0,0),"black");

    animation = animation_factory->createObject(QRect(300,300,40,40),":/images/explosion.png",5);

    base = block_factory->createObject();
    base->setDescription(QRect(350,530,30,30),":/images/base.png");
    base->setID(5);

    BrickMap.append(base);
    PlayerCollisions.append(base);

    gameover = block_factory->createObject();
    gameover->setDescription(QRect(300,300,100,100),":/images/logo.png");

    border = block_factory->createObject();
    border->setDescription(QRect(0,0,800,600),":/images/images/border.png");

    playercontrol = block_factory->createObject();
    playercontrol->setDescription(QRect(10,200,120,220),":/images/Control1");

    lifecounter = block_factory->createObject();
    lifecounter->setDescription(QRect(700,400,20,20),":/images/3.png");

    for(int i =0;i<13;i++)
    {
        for(int j =0;j<13;j++)
        {
            if(gameMap[i][j] == Brick){
            block = block_factory->createObject();
            block->setID(1);
            block->setDescription(QRect(40*j+140,40*i+40,40,40),":/images/brick.png");
            BrickMap.append(block);
            PlayerCollisions.append(block);
            }
            if(gameMap[i][j] == Green){
            block = block_factory->createObject();
            block->setID(2);
            block->setDescription(QRect(40*j+140,40*i+40,40,40),":/images/green.png");
            GreenMap.append(block);
            }
            if(gameMap[i][j] == Water)
            {
            block = block_factory->createObject();
            block->setID(3);
            block->setDescription(QRect(40*j+140,40*i+40,40,40),":/images/water.png");
            WaterMap.append(block);
            PlayerCollisions.append(block);
            }
            if(gameMap[i][j] == Steel)
            {
            block = block_factory->createObject();
            block->setID(4);
            block->setDescription(QRect(40*j+140,40*i+40,40,40),":/images/metal.png");
            BrickMap.append(block);
            PlayerCollisions.append(block);
            }
        }
    }

    EnemyCollisions = PlayerCollisions;



        player1->setColliding(PlayerCollisions);

    Pause = false;

    bullet = nullptr;
    Score = 0;
    pauser = 0;
    EnemyCount = 0;

    QSound::play(":/sound/sounds/levelstarting.wav");
}


void GameState::draw()
{


}

void GameState::clearList()
{
    qDeleteAll(Game::Instance().current->objects());
}

QVector <GameObject*> GameState::objects()
{
    gameobjects.clear();

    QVector <GameObject*> bullets;
    QVector <GameObject*> enemybullets;

    gameobjects.append(border);
    gameobjects.append(score);
    gameobjects.append(lifecounter);
    gameobjects.append(playerlifes);
    gameobjects.append(playercontrol);


    if (EnemyCount < 2)
    {
        for (int i = 0; i < 3-EnemyCount;i++)
        {
            int pos = rand()%4;
            enemy2 = enemy_factory->createObject();
            enemy2->setDescription(QRect(560 - pos * 50,40,30,30),":/images/images/EnemyDown.png");
            EnemyCollisions.append(enemy2);
            PlayerCollisions.append(enemy2);
            enemies.append(enemy2);
            EnemyCount++;
        }

    }

        if( player1->getLifes() == 0 || Lose ){
        gameobjects.append(gameover);
        QSound::play(":/sound/sounds/.wav");
        setHighscore();
        }

    foreach (GameObject* animation, Animations)
    {
        if(animation->isActive())
        {
            gameobjects.append(animation);
        }
        else
        {
            Animations.removeOne(animation);
            delete animation;
        }
    }

    foreach (GameObject* water, WaterMap)
    {
        gameobjects.append(water);
    }


        if(player1->bulletPointer() != nullptr){
        bullets.append(player1->bulletPointer());
        gameobjects.append(player1->bulletPointer());

        }


    foreach (GameObject* enemy, enemies) {
        if(enemy->bulletPointer() != nullptr ){
        gameobjects.append(enemy->bulletPointer());
        bullets.append(enemy->bulletPointer());
        enemybullets.append(enemy->bulletPointer());
        }
    }

    YouLose(enemybullets);

    KillEnemies(player1);



    foreach(GameObject * tonew,BulletsBlocks(bullets))
    {
       // if(tonew->isActive())
      gameobjects.append(tonew) ;
    }



    foreach(GameObject * tonew,BrickMap)
    {
      gameobjects.append(tonew);
    }




        if(player1->getLifes()>0)
        {
            player1->setColliding(PlayerCollisions);
            gameobjects.append(player1);
        }


    foreach (GameObject* tonew, enemies)
    {
        EnemyCollisions.removeOne(tonew);
        tonew->setColliding(EnemyCollisions);
        EnemyCollisions.append(tonew);
        gameobjects.append(tonew);
    }

    foreach (GameObject* green, GreenMap)
    {
        gameobjects.append(green);
    }

    if(Pause)
    {
        block = block_factory->createObject();
        block->setDescription(QRect(350,300,60,15),":/images/pause.png");
        QSound::play(":/sound/sounds/pause.wav");
        gameobjects.append(block);
        Game::Instance().WinGame->timer->stop();
    }

    return gameobjects;
}


QVector<GameObject *> GameState::BulletsBlocks(QVector<GameObject *> bullets)
{
    QVector <GameObject*> back;

    foreach(GameObject* bullet,bullets)
    {
        foreach(GameObject* block,BrickMap)
        {
            if( block->pos().intersects(bullet->pos()) )
            {
                if(block->getID() == 1){
                    Animations.append(animation_factory->createObject(QRect(block->getX(),block->getY(),40,40),":/images/explosion.png",5));
                    bullet->hited(true);

                    PlayerCollisions.removeOne(block);
                    EnemyCollisions.removeOne(block);

                    BrickMap.removeAt(BrickMap.indexOf(block));

                    delete block;
                    block = nullptr;

                    QSound::play(":/sound/sounds/brickhit.wav");

                }else{
                    if ( block->getID() == 4)
                    {
                        bullet->hited(true);
                        QSound::play(":/sound/sounds/steelhit.wav");
                    }

                    if (block->getID() == 5)
                        Lose = true;
                }
            }else{
                back.append(bullet);
            }
        }
    }
    return back;
}

void GameState::setHighscore()
{
    bool Entered;

    QString str = QInputDialog::getText( 0,
                                         "GAME OVER",
                                         "Enter Name:",
                                         QLineEdit::Normal,
                                         "",
                                         &Entered
                                        );
    if(Entered)
    {

    std::vector<data_player> data;

    QFile inputFile("C:\\Users\\Viktor\\Desktop\\NIGHT_WORK\\GAME_STATE\\Highscores.txt");

       inputFile.open(QFile::ReadOnly);
       QTextStream in(&inputFile);

       while (!in.atEnd())
       {
          QString line1 = in.readLine();
          QString line2 = in.readLine();
          data.push_back(data_player(line1,line2));
       }

       data.push_back(data_player(str,QString::number(Score)));

       std::sort(data.begin(),data.end());

       inputFile.close();

       inputFile.open(QFile::WriteOnly | QFile::Truncate);

       foreach(data_player scores, data)
       {
           inputFile.flush();
           in << scores.name;
           inputFile.flush();
           in << "\n";
           inputFile.flush();
           in << scores.score;
           inputFile.flush();
           in << "\n" ;
       }

       data.clear();
       inputFile.close();
    Game::Instance().setCurrent(new Highscores);
  //  delete this;

    }else
    {
        Game::Instance().setCurrent(Menu::Instance());
       // delete this;
    }
}

void GameState::KillEnemies(GameObject * player)
{
        foreach(GameObject* enemy , enemies)
        {
              if(player->bulletPointer() != nullptr)
              {
                if( enemy->pos().intersects(player->bulletPointer()->pos()) )
                {
                Animations.append(animation_factory->createObject(QRect(enemy->getX(),enemy->getY(),40,40),":/images/explosion.png",5));
                EnemyCount--;

                enemies.removeOne(enemy);
                PlayerCollisions.removeOne(enemy);
                EnemyCollisions.removeOne(enemy);

               // delete enemy->bulletPointer();
               // enemy->bulletPointer() = nullptr;

                delete enemy;
                enemy = nullptr;
                player->bulletPointer()->hited(true);

                Score++;
                QString str = QString("SCORE \n%1").arg(Score);
                score->drawText(str);
                QSound::play(":/sound/sounds/eexplosion.wav");
                QSound::play(":/sound/sounds/winner.wav");
                return;
                }
              }else{return;}
         }
}

void GameState::YouLose(QVector<GameObject *>bullets)
{
    foreach(GameObject* bullet,bullets)
    {
        if(player1->pos().intersects(bullet->pos()))
           {
            bullet->hited(true);
            Animations.append(animation_factory->createObject(QRect(player1->getX(),player1->getY(),35,35),":/images/explosion.png",5));
            player1->die();
            QString str = QString(":/images/%1.png").arg(player1->getLifes());
            lifecounter->setDescription(QRect(700,400,20,20),str);
           }
    }

}


void GameState::mouse(GameWidget*, QMouseEvent*)
{

}

void GameState::keyPress(QKeyEvent* event)
{
        switch (event->key()){

            case Qt::Key_Up :
                player1->moveUp();
                break;

            case Qt::Key_Down :
                player1->moveDown();
                break;

            case Qt::Key_Right :
                player1->moveRight();
                break;

            case Qt::Key_Left :
                player1->moveLeft();
                break;

            case Qt::Key_Space :
                player1->fire();
                break;

            case Qt::Key_P :
            if(Pause)
                {
                Pause = false;
                Game::Instance().WinGame->timer->start(16.666);
                }
            else
                {
                    Pause = true;
                }
            }

}

void GameState::keyRelease(GameWidget*, QKeyEvent* event, QTimer*)
{

        switch (event->key()){

            case Qt::Key_Up :
                player1->move();
                break;

            case Qt::Key_Down :
                 player1->move();
                break;

            case Qt::Key_Right :
                 player1->move();
                break;

            case Qt::Key_Left :
                 player1->move();
                break;
            }
}

GameState::~GameState()
{
//    qDeleteAll(players);
//    qDeleteAll(enemies);
//    qDeleteAll(BrickMap);
//    qDeleteAll(GreenMap);
//    qDeleteAll(WaterMap);


}
