#include <gtest/gtest.h>

#include "player.h"
#include "Square/gotoprison.h"
#include "Square/prison.h"
#include "Square/reward.h"
#include "Square/penalty.h"

#include "Mocks/dicemock.h"

using namespace ::testing;

namespace{
constexpr unsigned int PRICE_FOR_REWARD = 20;
constexpr unsigned int PRICE_FOR_PENALTY = 50;
}

class PlayerTestSuite: public Test
{
public:
    PlayerTestSuite():
        board(createSquares()),
        squares(createSquares()),
        sut("tester", board.createBoardIterator(), diceMock)
        {}

    Board board;
    Squers squares;
    NiceMock<Dice> diceMock;
    Player sut;

    Squers createSquares();
};

Squers PlayerTestSuite::createSquares()
{
    Squers squares;
    squares.push_back(std::make_unique<Prison>());
    squares.push_back(std::make_unique<GoToPrison>(squares.begin()));
    squares.push_back(std::make_unique<Reward>(PRICE_FOR_REWARD));
    squares.push_back(std::make_unique<Penalty>(PRICE_FOR_PENALTY));
    return squares;
}

TEST_F(PlayerTestSuite, shouldChangePossitionToPrisionWhenItLockedInPrison)
{
    auto prisionPossition = squares.begin();

    sut.lockInPrison(prisionPossition);
    auto status = sut.status();

    auto prisionIt = BoardIterator(squares.begin(), squares.end(), prisionPossition);
    EXPECT_EQ(status.actualPossisionOnBoard, prisionIt);
}

TEST_F(PlayerTestSuite, shouldAddMoney)
{
    sut.addMoney(PRICE_FOR_REWARD);
    auto status = sut.status();
    EXPECT_EQ(status.money, moneyOnStartGame+PRICE_FOR_REWARD);
}