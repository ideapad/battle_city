#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>

class GameWidget : public QWidget
{
    Q_OBJECT
public:

    GameWidget(QWidget *parent = 0);
    ~GameWidget();
    QTimer* timer;
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *);
    int move;

private:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void moveImg();
    void moveImgInst();
};

#endif // GAMEWIDGET_H
