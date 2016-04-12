#ifndef ABOUT_H
#define ABOUT_H

#include "state.h"
#include "factory.h"
#include "QKeyEvent"

class About : public State
{
public:
    static About* Instance();
    QVector<GameObject *> objects();
    void draw();
    void clearList();
    void mouse(GameWidget*, QMouseEvent*);
    void keyPress(QKeyEvent*);
    void keyRelease(GameWidget*, QKeyEvent*, QTimer*);
private:
    TextFactory* text_factory;
    BlockFactory* block_factory;
    GameObject *logo,*items,*pointer;
    short int MenuItem;
    About();
    About(const About& root);
    About& operator=(const About&);
    static About* _instance;

};


#endif // ABOUT_H
