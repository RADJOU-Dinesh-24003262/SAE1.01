TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    maze.cpp

include(MinGL2_IUT_AIX-master/mingl.pri)
