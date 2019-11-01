#include <gtest/gtest.h>

#include "Mocks/dicemock.h"
#include "Square/property.h"
#include "player.h"
#include "Square/publicfacilities.h"

namespace{
constexpr unsigned int FACTOR_OWNER_HAVE_ONE_FACILITY = 4;
constexpr unsigned int FACTOR_OWNER_HAVE_TWO_FACILITY = 10;

constexpr unsigned int WATER_SUPPLY_PRICE = 100;
const std::string WATER_SUPPLY_NAME = "Wodociagi";

constexpr unsigned int POWER_STATION_PRICE = 100;
const std::string POWER_STATION_NAME = "Elektrownia";
}

class PropertyPublicFacilitiesTestSuite: public ::testing::Test
{
public:
    PropertyPublicFacilitiesTestSuite()
    {
        setupPropertyWithPublicFacilitesPayMode();
        playerFirst = std::make_unique<Player>("tester Marek", BoardIterator(propertisSut.begin(), propertisSut.end()), dice);
        playerSecond = std::make_unique<Player>("tester Dawid", BoardIterator(propertisSut.begin(), propertisSut.end()), dice);
    }

    ::testing::NiceMock<DiceMock> dice;
    std::unique_ptr<Player> playerFirst;
    std::unique_ptr<Player> playerSecond;
    District district;
    Squers propertisSut;

    void setupPropertyWithPublicFacilitesPayMode();
    void diceRoll(unsigned int steps);
};

void PropertyPublicFacilitiesTestSuite::setupPropertyWithPublicFacilitesPayMode()
{
    auto waterSupply = std::make_unique<Property>(WATER_SUPPLY_PRICE, std::make_unique<PublicFacilities>(district), WATER_SUPPLY_NAME);
    auto powerStation = std::make_unique<Property>(POWER_STATION_PRICE, std::make_unique<PublicFacilities>(district), POWER_STATION_NAME);

    district.assignPropertisToDistrict({waterSupply.get(), powerStation.get()});

    propertisSut.push_back(std::move(waterSupply));
    propertisSut.push_back(std::move(powerStation));
}

void PropertyPublicFacilitiesTestSuite::diceRoll(unsigned int steps)
{
    ON_CALL(dice, diceThrow()).WillByDefault(::testing::Return(steps));
}

TEST_F(PropertyPublicFacilitiesTestSuite, dawidShouldPayRentForMarekWhenMarekHaveOnlyPowerStation)
{
    unsigned int steps = 1;
    diceRoll(steps);

    playerFirst->turn();

    unsigned int rollDice = 4;
    EXPECT_CALL(dice, diceThrow()).Times(2).
            WillOnce(::testing::Return(steps)).
            WillOnce(::testing::Return(rollDice));
    playerSecond->turn();

    auto statusMarek = playerFirst->status();
    auto statusDawid = playerSecond->status();

    auto expectedRent = FACTOR_OWNER_HAVE_ONE_FACILITY * rollDice;
    const auto expectedMoneyForMarek = moneyOnStartGame - POWER_STATION_PRICE + expectedRent;
    EXPECT_EQ(statusMarek.money(), expectedMoneyForMarek);

    const auto expectedMoneyForDawid = moneyOnStartGame - expectedRent;
    EXPECT_EQ(statusDawid.money(), expectedMoneyForDawid);
}

TEST_F(PropertyPublicFacilitiesTestSuite, dawidShouldPayRentForMarekWhenMarekHaveTwoPublicFacilities)
{
    unsigned int steps = 1;
    unsigned int rollDiceFirstTurn = 4;
    unsigned int rollDiceSecondTurn = 5;

    EXPECT_CALL(dice, diceThrow()).Times(6).
            WillOnce(::testing::Return(steps)). //Marek run to Elektrownia and buy it
            WillOnce(::testing::Return(steps)). //Dawid run to Electrownia
            WillOnce(::testing::Return(rollDiceFirstTurn)). //Dawid roll dice to pay rent
            WillOnce(::testing::Return(steps)). //Marek run to Wodociagi and buy it
            WillOnce(::testing::Return(steps)). //Dawid run to Wodociagi
            WillOnce(::testing::Return(rollDiceSecondTurn)); //Dawid roll dice to pay rent

    playerFirst->turn();
    playerSecond->turn();

    playerFirst->turn();
    playerSecond->turn();

    auto expectedRentFirstTurn = FACTOR_OWNER_HAVE_ONE_FACILITY * rollDiceFirstTurn;
    auto expectedRentSecondTurn = FACTOR_OWNER_HAVE_TWO_FACILITY * rollDiceSecondTurn;

    auto statusMarek = playerFirst->status();
    auto statusDawid = playerSecond->status();

    const auto expectedMoneyForMarek = moneyOnStartGame - POWER_STATION_PRICE + expectedRentFirstTurn
                                                        - WATER_SUPPLY_PRICE + expectedRentSecondTurn;
    EXPECT_EQ(statusMarek.money(), expectedMoneyForMarek);

    const auto expectedMoneyForDawid = moneyOnStartGame - expectedRentFirstTurn - expectedRentSecondTurn;
    EXPECT_EQ(statusDawid.money(), expectedMoneyForDawid);
}

