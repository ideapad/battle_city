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
#include "multiplayer.h"


enum {Empty,Brick,Green,Water,Steel};
enum{Singleplayer,Multiplayer};

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


Multiplayer::Multiplayer()
{
    Lose = false;

    BulletHit = false;

    player_factory    =    new PlayerFactory;
    enemy_factory     =    new EnemyFactory;
    block_factory     =    new BlockFactory;
    text_factory      =    new TextFactory;
    animation_factory =    new AnimationFactory;


    block = block_factory->createObject();

    player1 = player_factory->createObject();
    players.append(player1);

    playerlifes = block_factory->createObject();
    playerlifes->setDescription(QRect(680,380,40,40),":/images/player1.png");
    score = text_factory->createObject(110,100);
    score->setText("SCORE \n 0",QRect(680,220,0,0),"black");

       player2 = player_factory->createObject();
       player2->setType(QPoint(380,530),2);
       players.append(player2);

       playerlifes1 = block_factory->createObject();
       playerlifes1->setDescription(QRect(680,440,40,40),":/images/player2.png");

       lifecounter1 = block_factory->createObject();
       lifecounter1->setDescription(QRect(700,460,20,20),":/images/3.png");


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

    lifecounter = block_factory->createObject();
    lifecounter->setDescription(QRect(700,400,20,20),":/images/3.png");

    playercontrol1 = block_factory->createObject();
    playercontrol1->setDescription(QRect(10,50,120,220),":/images/Control1");
    playercontrol2 = block_factory->createObject();
    playercontrol2->setDescription(QRect(10,300,120,220),":/images/Control2");

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

    foreach(GameObject* player,players)
    {
        player->setColliding(PlayerCollisions);
    }

    hitBullet = true;
    bullet = nullptr;
    Score = 0;
    pauser = 0;
    EnemyCount = 0;

     QSound::play(":/sound/sounds/levelstarting.wav");
}


void Multiplayer::draw()
{


}

void Multiplayer::clearList()
{
    qDeleteAll(Game::Instance().current->objects());
}

QVector <GameObject*> Multiplayer::objects()
{
    gameobjects.clear();

    QVector <GameObject*> bullets;
    QVector <GameObject*> enemybullets;

    gameobjects.append(border);
    gameobjects.append(score);
    gameobjects.append(lifecounter);
    gameobjects.append(playerlifes);
    gameobjects.append(playercontrol1);
    gameobjects.append(playercontrol2);
    gameobjects.append(playerlifes1);
    gameobjects.append(lifecounter1);


    if (EnemyCount < 2)
    {
        for (int i = 0; i < 3-EnemyCount;i++)
        {
            int pos = rand()%4;
            enemy = enemy_factory->createObject();
            enemy->setDescription(QRect(560 - pos * 50,40,30,30),":/images/images/EnemyDown.png");
            EnemyCollisions.append(enemy);
            PlayerCollisions.append(enemy);
            enemies.append(enemy);
            EnemyCount++;
        }

    }


            if( ((player1->getLifes() == 0) && (player2->getLifes() == 0)) || Lose ){
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

    foreach(GameObject* player,players)
    {
        if(player->bulletPointer() != nullptr){
        gameobjects.append(player->bulletPointer());
        bullets.append(player->bulletPointer());
        }
    }

    foreach (GameObject* enemy, enemies) {
        if(enemy->bulletPointer() != nullptr){
        gameobjects.append(enemy->bulletPointer());
        bullets.append(enemy->bulletPointer());
        enemybullets.append(enemy->bulletPointer());
        }
    }

    YouLose(enemybullets);

    KillEnemies(player1);
    KillEnemies(player2);


    foreach(GameObject * tonew,BulletsBlocks(bullets))
    {
       // if(tonew->isActive())
      gameobjects.append(tonew) ;
    }



    foreach(GameObject * tonew,BrickMap)
    {
      gameobjects.append(tonew);
    }

    foreach (GameObject* green, GreenMap)
    {
        gameobjects.append(green);
    }

    foreach (GameObject* player, players) {
        if(player->getLifes()>0)
        {
            player->setColliding(PlayerCollisions);
            gameobjects.append(player);
        }
    }

    foreach (GameObject* tonew, enemies)
    {
        EnemyCollisions.removeOne(tonew);
        tonew->setColliding(EnemyCollisions);
        EnemyCollisions.append(tonew);
        gameobjects.append(tonew);
    }

    if(Pause)
    {
        block = block_factory->createObject();
        block->setDescription(QRect(400,300,60,15),":/images/pause.png");
        QSound::play(":/sound/sounds/pause.wav");
        gameobjects.append(block);
        Game::Instance().WinGame->timer->stop();
    }


    return gameobjects;
}


QVector<GameObject *> Multiplayer::BulletsBlocks(QVector<GameObject *> bullets)
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

void Multiplayer::setHighscore()
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

void Multiplayer::KillEnemies(GameObject * player)
{
        foreach(GameObject* enemy , enemies)
        {
//            foreach (GameObject* player, players)
//            {
              if(player->bulletPointer() != nullptr)
              {
                if( enemy->pos().intersects(player->bulletPointer()->pos()) )
                {
                Animations.append(animation_factory->createObject(QRect(enemy->getX(),enemy->getY(),40,40),":/images/explosion.png",5));
                EnemyCount--;

                enemies.removeOne(enemy);
                PlayerCollisions.removeOne(enemy);
                EnemyCollisions.removeOne(enemy);
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
         //   }
         }
}

void Multiplayer::YouLose(QVector<GameObject *>bullets)
{
    foreach(GameObject* bullet,bullets)
    {

      foreach (GameObject* player, players){
        if(player->pos().intersects(bullet->pos()))
           {
            Animations.append(animation_factory->createObject(QRect(player->getX(),player->getY(),35,35),":/images/explosion.png",5));
            player->die();
            QString str = QString(":/images/%1.png").arg(player->getLifes());
            if(player->getType() == 1){
            lifecounter->setDescription(QRect(700,400,20,20),str);}
            else{
            lifecounter1->setDescription(QRect(700,460,20,20),str);
            }
           }
        }

      if(player1->getLifes() < 1)
          players.removeOne(player1);
      if(player2->getLifes() < 1)
          players.removeOne(player2);



    }

}


void Multiplayer::mouse(GameWidget*, QMouseEvent*)
{

}

void Multiplayer::keyPress(QKeyEvent* event)
{
    switch (event->key()){

    case Qt::Key_W :
        if(player1->getLifes() > 0)
        player1->moveUp();
        break;

    case Qt::Key_S :
        if(player1->getLifes() > 0)
        player1->moveDown();
        break;

    case Qt::Key_D :
        if(player1->getLifes() > 0)
        player1->moveRight();
        break;

    case Qt::Key_A :
        if(player1->getLifes() > 0)
        player1->moveLeft();
        break;

    case Qt::Key_Space :
        if(player1->getLifes() > 0)
        player1->fire();
        break;

    case Qt::Key_Up :
        if(player2->getLifes() > 0)
        player2->moveUp();
        break;

    case Qt::Key_Down :
        if(player2->getLifes() > 0)
        player2->moveDown();
        break;

    case Qt::Key_Right :
        if(player2->getLifes() > 0)
        player2->moveRight();
        break;

    case Qt::Key_Left :
        if(player2->getLifes() > 0)
        player2->moveLeft();
        break;

    case Qt::Key_Control :
        if(player2->getLifes() > 0)
        player2->fire();
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

void Multiplayer::keyRelease(GameWidget*, QKeyEvent* event, QTimer*)
{

    switch (event->key()){

    case Qt::Key_W :
        player1->move();
        break;

    case Qt::Key_S :
        player1->move();
        break;

    case Qt::Key_D :
        player1->move();
        break;

    case Qt::Key_A :
        player1->move();
        break;

    case Qt::Key_Up :
        player2->move();
        break;

    case Qt::Key_Down :
        player2->move();
        break;

    case Qt::Key_Right :
        player2->move();
        break;

    case Qt::Key_Left :
        player2->move();
        break;

    }

}

Multiplayer::~Multiplayer()
{
//    qDeleteAll(players);
//    qDeleteAll(enemies);
//    qDeleteAll(BrickMap);
//    qDeleteAll(GreenMap);
//    qDeleteAll(WaterMap);


}

