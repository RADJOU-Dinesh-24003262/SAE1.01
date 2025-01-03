TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Jeu/game.cpp \
    Jeu/gridmanagement.cpp \
    Jeu/params.cpp \
    main.cpp

DISTFILES += \
    Nos_fichiers/config.yaml

HEADERS += \
    Jeu/game.h \
    Jeu/gridmanagement.h \
    Jeu/params.h \
    Jeu/type.h

HEADERS += \
    sprites/player1.h \
    sprites/player2.h \
    sprites/wall.h \


include(MinGL2_IUT_AIX-master/mingl.pri)

