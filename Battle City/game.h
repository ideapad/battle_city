#ifndef GAME_H
#define GAME_H

#include "gamewidget.h"
#include "state.h"
#include <QPainter>
#include <QList>


class Game
{

public:
    GameWidget *WinGame;
    static Game& Instance();
    void run();
    class State *current;
    void draw(QPainter* painter);
    void setCurrent(State *s)
    {
        current = s;
    }
    State* getState(Game *);

private:
    Game();
    Game(const Game& root);
    Game& operator=(const Game&);
};

#endif // GAME_H
