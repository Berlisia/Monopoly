TEMPLATE = app
CONFIG += console c++11
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
    deposite.cpp \
    piece.cpp

HEADERS += \
    square.h \
    start.h \
    board.h \
    monopolygame.h \
    player.h \
    piece.h \
    die.h \
    penalty.h \
    reward.h \
    cycliciterator.h \
    deposite.h
