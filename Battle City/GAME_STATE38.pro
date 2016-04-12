#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T00:35:43
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QMAKE_CXXFLAGS += -std=c++0x
CONFIG += qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GAME_STATE
TEMPLATE = app


SOURCES += main.cpp\
        gamewidget.cpp \
    state.cpp \
    game.cpp \
    loading.cpp \
    menu.cpp \
    gamestate.cpp \
    highscores.cpp \
    log.cpp \
    gameobj.cpp \
    factory.cpp \
    about.cpp \
    multiplayer.cpp \
    data_player.cpp \
    player.cpp \
    enemy.cpp \
    block.cpp \
    bullet.cpp \
    text.cpp \
    animation.cpp

HEADERS  += gamewidget.h \
    state.h \
    game.h \
    loading.h \
    menu.h \
    gamestate.h \
    highscores.h \
    log.h \
    gameobj.h \
    factory.h \
    about.h \
    multiplayer.h \
    data_player.h \
    player.h \
    enemy.h \
    block.h \
    bullet.h \
    text.h \
    animation.h

RESOURCES += \
    images.qrc \
    sound.qrc
