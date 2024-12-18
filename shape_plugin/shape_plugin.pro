TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    maze.cpp

HEADERS += \
    sprites/player1.h \
    sprites/player2.h \
    sprites/wall.h \


include(MinGL2_IUT_AIX-master/mingl.pri)
