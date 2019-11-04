#include <gtest/gtest.h>

#include "Mocks/dicemock.h"
#include "Square/property.h"
#include "player.h"
#include "Square/buildingproperty.h"

namespace{
constexpr unsigned int HOUSE_PRICE = 10;
constexpr unsigned int HOTEL_PRICE = 50;

constexpr unsigned int PUB_PRICE = 100;
const std::string PUB_NAME = "Karczma 7 kotow";
const RentAtNumberOfBuildings PUB_RENT_BUILDING = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
constexpr Rent PUB_RENT = 5;

constexpr unsigned int EXPENSIVE_PRICE = 500;
const std::string EXPENSIVE_NAME = "Zimorodek";
const RentAtNumberOfBuildings EXPENSIVE_RENT_BUILDING = {{1, 20}, {2, 30}, {3, 40}, {4, 50}, {5, 60}};
constexpr Rent EXPENSIVE_RENT = 10;

constexpr unsigned int BEAR_PRICE = 200;
const std::string BEAR_NAME = "Niedzwiedzia chata";
const RentAtNumberOfBuildings BEAR_RENT_BUILDING = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
constexpr Rent BEAR_RENT = 5;

}

class PropertyTestSuite: public ::testing::Test
{
public:
    PropertyTestSuite()
    {
        setupTestBoard();
        playerFirst = std::make_unique<Player>("tester Marek", BoardIterator(propertisSut.begin(), propertisSut.end()), dice);
        playerSecond = std::make_unique<Player>("tester Dawid", BoardIterator(propertisSut.begin(), propertisSut.end()), dice);
    }

    ::testing::NiceMock<DiceMock> dice;
    std::unique_ptr<Player> playerFirst;
    std::unique_ptr<Player> playerSecond;
    std::vector<District> districts;
    std::vector<HouseDevelop*> buildingModes;
    Squers propertisSut;

    void setupTestBoard();
    void diceRoll(unsigned int steps);
};

void PropertyTestSuite::setupTestBoard()
{
    districts.push_back(District());
    districts.push_back(District());
    auto buildingModeForPub = std::make_unique<BuildingProperty>(PUB_RENT, PUB_RENT_BUILDING, districts[0], HOUSE_PRICE, HOTEL_PRICE);
    auto buildingModeForBear = std::make_unique<BuildingProperty>(BEAR_RENT, BEAR_RENT_BUILDING, districts[0], HOUSE_PRICE, HOTEL_PRICE);
    auto buildingModeForExpensive = std::make_unique<BuildingProperty>(EXPENSIVE_RENT, EXPENSIVE_RENT_BUILDING, districts[0], HOUSE_PRICE, HOTEL_PRICE);

    buildingModes.push_back(buildingModeForPub.get());
    buildingModes.push_back(buildingModeForBear.get());
    buildingModes.push_back(buildingModeForExpensive.get());

    auto propertyPub = std::make_unique<Property>(PUB_PRICE, std::move(buildingModeForPub), PUB_NAME);
    auto propertyBear = std::make_unique<Property>(BEAR_PRICE, std::move(buildingModeForBear), BEAR_NAME);
    auto propertyExpensive = std::make_unique<Property>(EXPENSIVE_PRICE, std::move(buildingModeForExpensive), EXPENSIVE_NAME);

    districts[0].assignPropertisToDistrict({propertyPub.get(), propertyBear.get()});
    districts[1].assignPropertisToDistrict({propertyExpensive.get()});

    propertisSut.push_back(std::move(propertyPub));
    propertisSut.push_back(std::move(propertyBear));
    propertisSut.push_back(std::move(propertyExpensive));
}

void PropertyTestSuite::diceRoll(unsigned int steps)
{
    ON_CALL(dice, diceThrow()).WillByDefault(::testing::Return(steps));
}

TEST_F(PropertyTestSuite, playerSecondShouldPayRentForPlayerFirst_OnePropertyInDistrict)
{
    unsigned int steps = 1;

    diceRoll(steps);

    playerFirst->turn();
    playerSecond->turn();

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - BEAR_PRICE + BEAR_RENT;
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame - BEAR_RENT;
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}

TEST_F(PropertyTestSuite, playerSecondShouldPayRentx2ForPlayerFirst_AllPropertyInDistrict)
{
    unsigned int steps = 1;

    diceRoll(steps);
    playerFirst->turn();
    playerSecond->turn();

    diceRoll(steps + 1);
    playerFirst->turn();
    playerSecond->turn();

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame -
                                             BEAR_PRICE -
                                             PUB_PRICE +
                                             BEAR_RENT +
                                             (PUB_RENT * 2);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame -
                                              BEAR_RENT -
                                              (PUB_RENT * 2);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}
