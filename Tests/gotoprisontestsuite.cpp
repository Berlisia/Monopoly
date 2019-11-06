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
        simpleBoard(createSimpleSquares()),
        playerMock("tester", simpleBoard.createBoardIterator(), diceMock, subjectBuildingProperty),
        sut(prisonPossisionOnBoard){}


    Board simpleBoard;
    Squers::iterator prisonPossisionOnBoard;
    SubjectBuildingProperty subjectBuildingProperty;

    NiceMock<Dice> diceMock;
    StrictMock<PlayerMock> playerMock;

    GoToPrison sut;

    Squers createSimpleSquares();
};

Squers GoToPrisonTestSuite::createSimpleSquares()
{
    Squers squares;
    squares.push_back(std::make_unique<Prison>());
    squares.push_back(std::make_unique<GoToPrison>(squares.begin()));
    prisonPossisionOnBoard = squares.begin();
    return squares;
}

TEST_F(GoToPrisonTestSuite, shouldPayerLockInPrisonWhenStopOn)
{
    EXPECT_CALL(playerMock, lockInPrison(prisonPossisionOnBoard));
    sut.actionOnStop(playerMock);
}
