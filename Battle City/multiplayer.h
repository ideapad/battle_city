#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "highscores.h"
#include "game.h"
#include "menu.h"
#include "gamestate.h"


class Multiplayer : public QObject, public State
{
    Q_OBJECT

public:

     Multiplayer();
     ~Multiplayer();

    Bullet* bullet;
    bool hitBullet;


    QVector<GameObject *> objects();


    void draw();
    void clearList();
    void mouse(GameWidget*, QMouseEvent*);
    void keyPress(QKeyEvent*);
    void keyRelease(GameWidget*, QKeyEvent*, QTimer*);
private:

    PlayerFactory* player_factory;
    EnemyFactory* enemy_factory;
    BlockFactory* block_factory;
    BulletFactory* bullet_factory;
    TextFactory* text_factory;
    AnimationFactory* animation_factory;

    void setHighscore();

    bool Lose;
    bool Pause;
    int Score;

    QVector<GameObject*> Animations;
    QVector<GameObject*> BrickMap;
    QVector<GameObject*> GreenMap;
    QVector<GameObject*> WaterMap;
    QVector<GameObject*> MetallMap;
    QVector<GameObject*> PlayerCollisions;
    QVector<GameObject*> EnemyCollisions;
    QVector<GameObject*> enemies;
    QVector<GameObject*> players;

    QVector<GameObject*> gameobjects;

    QVector<GameObject *> BulletsBlocks(QVector <GameObject*>);

    void KillEnemies(GameObject*);
    void YouLose(QVector<GameObject*>);

    int EnemyCount;
    int TypeGame;

    bool BulletHit;
    GameObject *animation,*base,*playerlifes,*playerlifes1,*lifecounter,*lifecounter1,*score;
    GameObject *player1,*player2,*bullet1,*playercontrol1,*playercontrol2,*enemy,*block,*gameover,*border;
    int pauser;

};

#endif // MULTIPLAYER_H
