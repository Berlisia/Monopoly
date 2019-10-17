TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    start.cpp \
    board.cpp \
    monopolygame.cpp \
    penalty.cpp \
    reward.cpp \
    player.cpp \
    deposite.cpp

HEADERS += \
    square.h \
    start.h \
    board.h \
    monopolygame.h \
    player.h \
    die.h \
    penalty.h \
    reward.h \
    cycliciterator.h \
    deposite.h
