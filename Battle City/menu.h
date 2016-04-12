#ifndef MENU_H
#define MENU_H

#include "state.h"
#include "factory.h"

class Menu : public State
{
public:
    static Menu* Instance();
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
    Menu();
    Menu(const Menu& root);
    Menu& operator=(const Menu&);
    static Menu* _instance;

};

#endif // MENU_H
