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
p
