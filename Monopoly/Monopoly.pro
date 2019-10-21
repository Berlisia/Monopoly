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
    deposite.cpp \
    property.cpp \
    randomsquare.cpp \
    blackhole.cpp \
    prison.cpp

HEADERS += \
    event.h \
    square.h \
    start.h \
    board.h \
    monopolygame.h \
    player.h \
    die.h \
    penalty.h \
    reward.h \
    cycliciterator.h \
    deposite.h \
    property.h \
    randomsquare.h \
    blackhole.h \
    prison.h \
    state.h \
    stateMachine.h \
    stateactiveplayer.h \
    stateplayerinprison.h \
    stateplayerbancrut.h
