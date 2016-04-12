#ifndef LOADING_H
#define LOADING_H

#include "state.h"
#include <QWidget>
#include "factory.h"

class Loading : public State
{
public:
    QVector<GameObject *> objects();
    static Loading* Instance();
    void draw();
    void clearList();
    void mouse(GameWidget*, QMouseEvent*);
    void keyPress(QKeyEvent*);
    void keyRelease(GameWidget*, QKeyEvent*, QTimer*);
private:
    BlockFactory* block_factory;
    GameObject* load;
    int pauser;
    Loading();
    Loading(const Loading& root);
    Loading& operator=(const Loading&);
    static Loading* _instance;

};

#endif // LOADING_H
