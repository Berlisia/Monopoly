#include <gtest/gtest.h>

#include "Mocks/dicemock.h"
#include "Square/property.h"
#include "player.h"
#include "Square/buildingproperty.h"

namespace{
constexpr unsigned int PUB_PRICE = 100;
const std::string PUB_NAME = "Karczma 7 kotow";
const Rent PUB_RENT = {{1, 10}, {2, 20}};

constexpr unsigned int EXPENSIVE_PRICE = 500;
const std::string EXPENSIVE_NAME = "Zimorodek";
const Rent EXPENSIVE_RENT = {{1, 30}};

constexpr unsigned int BEAR_PRICE = 200;
const std::string BEAR_NAME = "Niedzwiedzia chata";
const Rent BEAR_RENT = {{1, 20}, {2, 40}};

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
    Squers propertisSut;

    void setupTestBoard();
    void diceRoll(unsigned int steps);
};

void PropertyTestSuite::setupTestBoard()
{
    districts.push_back(District());
    districts.push_back(District());
    auto propertyPub = std::make_unique<Property>(PUB_PRICE, std::make_unique<BuildingProperty>(PUB_RENT, districts[0]), PUB_NAME);
    auto propertyBear = std::make_unique<Property>(BEAR_PRICE, std::make_unique<BuildingProperty>(BEAR_RENT, districts[0]), BEAR_NAME);
    auto propertyExpensive = std::make_unique<Property>(EXPENSIVE_PRICE, std::make_unique<BuildingProperty>(EXPENSIVE_RENT, districts[0]), EXPENSIVE_NAME);

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
    unsigned int haveOnePropertyFromDistrict = 1;

    diceRoll(steps);

    playerFirst->turn();
    playerSecond->turn();

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - BEAR_PRICE + BEAR_RENT.at(haveOnePropertyFromDistrict);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame - BEAR_RENT.at(haveOnePropertyFromDistrict);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}

TEST_F(PropertyTestSuite, playerSecondShouldPayRentForPlayerFirst_TwoPropertyInDistrict)
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
                                             BEAR_PRICE -
                                             PUB_PRICE +
                                             BEAR_RENT.at(haveOnePropertyFromDistrict) +
                                             PUB_RENT.at(haveTwoPropertyFromDistrict);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame -
                                              BEAR_RENT.at(haveOnePropertyFromDistrict) -
                                              PUB_RENT.at(haveTwoPropertyFromDistrict);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}
