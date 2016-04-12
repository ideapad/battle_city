#include "game.h"
#include "loading.h"
#include "menu.h"
#include "gamestate.h"
#include "highscores.h"

Game::Game()
{
    WinGame = new GameWidget;
    WinGame->setPalette( QPalette( Qt::black ));
    current = Loading::Instance();
}

Game& Game::Instance()
{
    static Game theSingleInstance;
    return theSingleInstance;
}

void Game::run()
{
    WinGame->show();
}


State* Game::getState(Game *)
{
    return current;
}

void Game::draw(QPainter *painter)
{
    current->draw(painter);
}
