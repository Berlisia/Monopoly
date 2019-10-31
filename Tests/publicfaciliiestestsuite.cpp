#include <gtest/gtest.h>

#include "Mocks/dicemock.h"
#include "Square/property.h"
#include "player.h"
#include "Square/publicfacilities.h"

namespace{
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
    auto steps = 1;
    diceRoll(steps);

    playerFirst->turn();
    playerSecond->turn();
    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    auto expectedRent = FACTOR_OWNER_HAVE_TWO_FACILITY;

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - POWER_STATION_PRICE;

}

