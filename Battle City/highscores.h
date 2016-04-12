#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "state.h"
#include "factory.h"
#include "gameobj.h"

class Highscores : public State
{
public:
    QVector<GameObject *> objects();

    void draw();
    void clearList();
    void mouse(GameWidget*, QMouseEvent*);
    void keyPress(QKeyEvent*);
    void keyRelease(GameWidget*, QKeyEvent*, QTimer*);
    Highscores();
    ~Highscores();
private:
    TextFactory* text_factory;
    BlockFactory* block_factory;
    QList <GameObject*> table;


};


#endif // HIGHSCORES_H
