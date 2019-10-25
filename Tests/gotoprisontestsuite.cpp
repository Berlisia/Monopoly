#include <gtest/gtest.h>

#include "Square/gotoprison.h"
#include "Square/prison.h"

#include "Mocks/playerMock.h"
#include "Mocks/dicemock.h"

using namespace testing;

class GoToPrisonTestSuite: public Test
{
public:
    GoToPrisonTestSuite():
        boardIterator(),
        playerMock("tester", boardIterator, diceMock),
        sut(prisonPossisionOnBoard){}


    Squers simpleSquers;
    Board simpleBoard;
    BoardIterator boardIterator;
    Squers::iterator prisonPossisionOnBoard;

    NiceMock<Dice> diceMock;
    StrictMock<PlayerMock> playerMock;

    GoToPrison* sut;

    Squers createSimpleBoard();
};

Squers GoToPrisonTestSuite::createSimpleBoard()
{
    Squers squares;
    squares.push_back(std::make_unique<Prison>());
    squares.push_back(std::make_unique<GoToPrison>(squares.begin()));
    return squares;
}

TEST_F(GoToPrisonTestSuite, should)
{

}
