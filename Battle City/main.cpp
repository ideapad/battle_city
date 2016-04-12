#include "game.h"
#include "log.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    qInstallMessageHandler(Log::myMessageOutput);

    QApplication a(argc, argv);

    Game::Instance().run();

    qDebug() << "Game started.";


    return a.exec();
}
