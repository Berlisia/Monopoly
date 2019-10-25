TEMPLATE = app
LIBS += -pthread

CONFIG += console c++17 test unix pthread
CONFIG -= app_bundle
CONFIG -= qt

monopoly{
    TARGET = Monopoly
    SOURCES += main.cpp
}

test{
    DEFINES += GTEST_LINKED_AS_SHARED_LIBRARY=1
    TARGET = MonopolyTest
    SOURCES += ../Tests/monopolytestmain.cpp
}

unix{
    INCLUDEPATH += ../gtest/googletest/include gtest
    DEPENDPATH += ../gtest/build
    LIBS += -L../gtest/build/lib/ -lgtest
}

win32{

}

SOURCES += \
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
    Square/penalty.h \
    guest.h
