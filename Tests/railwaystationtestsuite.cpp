#include <gtest/gtest.h>

#include "Mocks/dicemock.h"
#include "Square/property.h"
#include "player.h"
#include "Square/railwaystation.h"

namespace{
const RentAtNumberOfRailways RENT = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};

constexpr unsigned int MAIN_PRICE = 100;
const std::string MAIN_NAME = "Glowny";

constexpr unsigned int SWIEBODZKI_PRICE = 100;
const std::string SWIEBODZKI_NAME = "Swiebodzki";

constexpr unsigned int MIKOLAJOW_PRICE = 100;
const std::string MIKOLAJOW_NAME = "Mikolajow";

constexpr unsigned int BROCHOW_PRICE = 100;
const std::string BROCHOW_NAME = "Brochow";

}

class PropertyRailwayStationTestSuite: public ::testing::Test
{
public:
    PropertyRailwayStationTestSuite()
    {
        setupTestBoard();
        playerFirst = std::make_unique<Player>("tester Marek", BoardIterator(propertisSut.begin(), propertisSut.end()), dice, subjectBuildingProperty);
        playerSecond = std::make_unique<Player>("tester Dawid", BoardIterator(propertisSut.begin(), propertisSut.end()), dice, subjectBuildingProperty);
    }

    ::testing::NiceMock<DiceMock> dice;
    SubjectBuildingProperty subjectBuildingProperty;
    std::unique_ptr<Player> playerFirst;
    std::unique_ptr<Player> playerSecond;
    District districts;
    Squers propertisSut;

    void setupTestBoard();
    void diceRoll(unsigned int steps);
};

void PropertyRailwayStationTestSuite::setupTestBoard()
{
    auto mainRailway = std::make_unique<Property>(MAIN_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, MAIN_NAME);
    auto swiebodzki = std::make_unique<Property>(SWIEBODZKI_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, SWIEBODZKI_NAME);
    auto mikolajow = std::make_unique<Property>(MIKOLAJOW_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, MIKOLAJOW_NAME);
    auto brochow = std::make_unique<Property>(BROCHOW_PRICE, std::make_unique<RailwayStation>(RENT, districts), districts, BROCHOW_NAME);

    districts.assignPropertisToDistrict({mainRailway.get(), swiebodzki.get(), mikolajow.get(), brochow.get()});

    propertisSut.push_back(std::move(mainRailway));
    propertisSut.push_back(std::move(swiebodzki));
    propertisSut.push_back(std::move(mikolajow));
    propertisSut.push_back(std::move(brochow));
}

void PropertyRailwayStationTestSuite::diceRoll(unsigned int steps)
{
    ON_CALL(dice, diceThrow()).WillByDefault(::testing::Return(steps));
}

TEST_F(PropertyRailwayStationTestSuite, playerSecondShouldPayRentForPlayerFirst_OnePropertyInDistrict)
{
    unsigned int steps = 1;
    unsigned int haveOnePropertyFromDistrict = 1;

    diceRoll(steps);

    playerFirst->turn();
    playerSecond->turn();

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - SWIEBODZKI_PRICE + RENT.at(haveOnePropertyFromDistrict);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame - RENT.at(haveOnePropertyFromDistrict);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}

TEST_F(PropertyRailwayStationTestSuite, playerSecondShouldPayRentForPlayerFirst_TwoPropertyInDistrict)
{
    unsigned int steps = 1;
    unsigned int haveOnePropertyFromDistrict = 1;
    unsigned int haveTwoPropertyFromDistrict = 2;

    diceRoll(steps);
    playerFirst->turn();
    playerSecond->turn();

    diceRoll(steps + 1);
    playerFirst->turn();
    playerSecond->turn();

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame -
                                             SWIEBODZKI_PRICE -
                                             MIKOLAJOW_PRICE +
                                             RENT.at(haveOnePropertyFromDistrict) +
                                             RENT.at(haveTwoPropertyFromDistrict);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame -
                                              RENT.at(haveOnePropertyFromDistrict) -
                                              RENT.at(haveTwoPropertyFromDistrict);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}
