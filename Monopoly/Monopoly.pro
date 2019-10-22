TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Square/start.cpp \
    board.cpp \
    monopolygame.cpp \
    Square/reward.cpp \
    player.cpp \
    Square/deposite.cpp \
    Square/property.cpp \
    Square/randomsquare.cpp \
    Square/blackhole.cpp \
    Square/prison.cpp \
    Square/penalty.cpp

HEADERS += \
    Square/square.h \
    Square/start.h \
    bank.h \
    bankier.h \
    board.h \
    monopolygame.h \
    player.h \
    die.h \
    Square/reward.h \
    cycliciterator.h \
    Square/deposite.h \
    Square/property.h \
    Square/randomsquare.h \
    Square/blackhole.h \
    Square/prison.h \
    state.h \
    stateMachine.h \
    stateactiveplayer.h \
    stateplayerinprison.h \
    stateplayerbancrut.h \
    Square/penalty.h
