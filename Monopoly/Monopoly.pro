TEMPLATE = app
LIBS += -pthread

CONFIG += console c++14 test win32 pthread
CONFIG -= app_bundle
CONFIG -= qt

monopoly{
    TARGET = Monopoly
    SOURCES += main.cpp
}

test{
    TARGET = MonopolyTest
    SOURCES += ../Tests/monopolytestmain.cpp \
        ../Tests/gotoprisontestsuite.cpp
    HEADERS += ../Tests/Mocks/playerMock.h \
        ../Tests/Mocks/guestmock.h
}

unix{
    INCLUDEPATH += ../gtest/googletest/include gtest
    DEPENDPATH += ../gtest/build
    LIBS += -L../gtest/build/lib/ -lgtest
}

win32{
    INCLUDEPATH += D:\Monopoly\googletest\googletest\include
    DEPENDPATH += D:\Monopoly\googletest\build
    LIBS += -LD:\Monopoly\googletest\build\lib\ -lgtest
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
    Square/penalty.cpp \
    Square/gotoprison.cpp

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
    guest.h \
    Square/gotoprison.h \
    ../Tests/Mocks/dicemock.h
