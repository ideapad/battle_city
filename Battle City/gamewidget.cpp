#include "gamewidget.h"
#include "game.h"
#include "loading.h"
#include "menu.h"
#include <QPainter>

#include <QtMultimedia/QSound>


#include <QTimer>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(800,600);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(16.666);
}

GameWidget::~GameWidget()
{

}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    foreach(GameObject* obj,Game::Instance().current->objects())
    {
        painter.drawPixmap(obj->pos(),obj->img());
    }

}

void GameWidget::timerEvent(QTimerEvent *)
{

}

void GameWidget::moveImg()
{

}

void GameWidget::moveImgInst()
{

}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    Game::Instance().current->keyPress(event);
}

void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    Game::Instance().current->keyRelease(this,event,timer);
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{

}

