#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T19:22:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hw9
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    key_paint_slots.h \
    lose_win_slots.h \
    minion_slots.h \
    player_slots.h \
    relic_actions.h \
    fire_slots.h

FORMS    += mainwindow.ui
