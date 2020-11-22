#include <gtest/gtest.h>

#include "Bankier.h"
#include "DiceMock.h"
#include "MonopolyGameFixture.h"
#include "Player.h"
#include "Property.h"
#include "RailwayStation.h"

namespace
{
const RentAtNumberOfRailways RENT = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};

constexpr unsigned int MAIN_PRICE = 100;
const std::string MAIN_NAME = "Glowny";

constexpr unsigned int SWIEBODZKI_PRICE = 100;
const std::string SWIEBODZKI_NAME = "Swiebodzki";

constexpr unsigned int MIKOLAJOW_PRICE = 100;
const std::string MIKOLAJOW_NAME = "Mikolajow";

constexpr unsigned int BROCHOW_PRICE = 100;
const std::string BROCHOW_NAME = "Brochow";

} // namespace

class PropertyRailwayStationTestSuite : public ::testing::Test
{
public:
    PropertyRailwayStationTestSuite() : board(std::move(setupTestBoard()))
    {
        playerFirst = std::make_unique<Player>("tester Marek", dice, subjectBuildingProperty);
        playerSecond = std::make_unique<Player>("tester Dawid", dice, subjectBuildingProperty);
    }

    ::testing::NiceMock<DiceMock> dice;
    SubjectBuildingProperty subjectBuildingProperty;
    std::unique_ptr<Contestant> playerFirst;
    std::unique_ptr<Contestant> playerSecond;
    District districts;
    Bankier bankier;
    Board board;

    Squers setupTestBoard();
    void diceRoll(unsigned int steps);
};

Squers PropertyRailwayStationTestSuite::setupTestBoard()
{
    Squers propertisSut;
    auto mainRailway = std::make_unique<Property>(
        MAIN_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, MAIN_NAME, bankier);
    auto swiebodzki = std::make_unique<Property>(
        SWIEBODZKI_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, SWIEBODZKI_NAME, bankier);
    auto mikolajow = std::make_unique<Property>(
        MIKOLAJOW_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, MIKOLAJOW_NAME, bankier);
    auto brochow = std::make_unique<Property>(
        BROCHOW_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, BROCHOW_NAME, bankier);

    districts.assignPropertisToDistrict({mainRailway.get(), swiebodzki.get(), mikolajow.get(), brochow.get()});

    propertisSut.push_back(std::move(mainRailway));
    propertisSut.push_back(std::move(swiebodzki));
    propertisSut.push_back(std::move(mikolajow));
    propertisSut.push_back(std::move(brochow));
    return propertisSut;
}

void PropertyRailwayStationTestSuite::diceRoll(unsigned int steps)
{
    ON_CALL(dice, diceThrow()).WillByDefault(::testing::Return(steps));
}

TEST_F(PropertyRailwayStationTestSuite, playerSecondShouldPayRentForPlayerFirst_OnePropertyInDistrict)
{
    MonopolyGameFixture game;
    unsigned int steps = 1;
    unsigned int haveOnePropertyFromDistrict = 1;
    auto possitionFirst = board.createBoardIterator();
    auto possitionSecond = board.createBoardIterator();

    diceRoll(steps);

    game.turn(*playerFirst, possitionFirst);
    game.turn(*playerSecond, possitionSecond);

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - SWIEBODZKI_PRICE + RENT.at(haveOnePropertyFromDistrict);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame - RENT.at(haveOnePropertyFromDistrict);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}

TEST_F(PropertyRailwayStationTestSuite, playerSecondShouldPayRentForPlayerFirst_TwoPropertyInDistrict)
{
    MonopolyGameFixture game;
    unsigned int steps = 1;
    unsigned int haveOnePropertyFromDistrict = 1;
    unsigned int haveTwoPropertyFromDistrict = 2;
    auto possitionFirst = board.createBoardIterator();
    auto possitionSecond = board.createBoardIterator();

    diceRoll(steps);
    game.turn(*playerFirst, possitionFirst);
    game.turn(*playerSecond, possitionSecond);

    diceRoll(steps + 1);
    game.turn(*playerFirst, possitionFirst);
    game.turn(*playerSecond, possitionSecond);

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - SWIEBODZKI_PRICE - MIKOLAJOW_PRICE +
        RENT.at(haveOnePropertyFromDistrict) + RENT.at(haveTwoPropertyFromDistrict);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond =
        moneyOnStartGame - RENT.at(haveOnePropertyFromDistrict) - RENT.at(haveTwoPropertyFromDistrict);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}
