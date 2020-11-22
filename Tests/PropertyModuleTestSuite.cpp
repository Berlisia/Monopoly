#include <gtest/gtest.h>

#include "Bankier.h"
#include "BuildingProperty.h"
#include "DiceMock.h"
#include "MonopolyGameFixture.h"
#include "Player.h"
#include "Property.h"

namespace
{
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

} // namespace

class PropertyTestSuite : public ::testing::Test
{
public:
    PropertyTestSuite() : board(std::move(setupTestBoard()))
    {
        playerFirst = std::make_unique<Player>("tester Marek", dice, subjectBuildingProperty);
        playerSecond = std::make_unique<Player>("tester Dawid", dice, subjectBuildingProperty);
    }

    ::testing::NiceMock<DiceMock> dice;
    SubjectBuildingProperty subjectBuildingProperty;
    std::unique_ptr<Contestant> playerFirst;
    std::unique_ptr<Contestant> playerSecond;
    std::vector<District> districts;
    std::vector<HouseDevelop*> buildingModes;
    Bankier bankier;
    Board board;

    void diceRoll(unsigned int steps) { ON_CALL(dice, diceThrow()).WillByDefault(::testing::Return(steps)); }

    Squers setupTestBoard()
    {
        districts.push_back(District());
        districts.push_back(District());
        auto buildingModeForPub = std::make_unique<BuildingProperty>(
            CardInfo{PUB_RENT, PUB_RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE, PUB_PRICE / 2}, districts[0]);
        auto buildingModeForBear = std::make_unique<BuildingProperty>(
            CardInfo{BEAR_RENT, BEAR_RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE, BEAR_PRICE / 2}, districts[0]);
        auto buildingModeForExpensive = std::make_unique<BuildingProperty>(
            CardInfo{EXPENSIVE_RENT, EXPENSIVE_RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE, EXPENSIVE_PRICE / 2},
            districts[1]);

        buildingModes.push_back(buildingModeForPub.get());
        buildingModes.push_back(buildingModeForBear.get());
        buildingModes.push_back(buildingModeForExpensive.get());

        subjectBuildingProperty.attach(buildingModeForBear.get());
        subjectBuildingProperty.attach(buildingModeForPub.get());
        subjectBuildingProperty.attach(buildingModeForExpensive.get());

        auto propertyPub =
            std::make_unique<Property>(PUB_PRICE, std::move(buildingModeForPub), districts[0], PUB_NAME, bankier);
        auto propertyBear =
            std::make_unique<Property>(BEAR_PRICE, std::move(buildingModeForBear), districts[0], BEAR_NAME, bankier);
        auto propertyExpensive = std::make_unique<Property>(
            EXPENSIVE_PRICE, std::move(buildingModeForExpensive), districts[1], EXPENSIVE_NAME, bankier);

        districts[0].assignPropertisToDistrict({propertyPub.get(), propertyBear.get()});
        districts[1].assignPropertisToDistrict({propertyExpensive.get()});

        Squers squers;
        squers.push_back(std::move(propertyPub));
        squers.push_back(std::move(propertyBear));
        squers.push_back(std::move(propertyExpensive));

        return squers;
    }
};

TEST_F(PropertyTestSuite, playerSecondShouldPayRentForPlayerFirst_OnePropertyInDistrict)
{
    unsigned int steps = 1;
    auto startPossitionPlayerFirst = board.createBoardIterator();
    auto startPossitionPlayerSecond = board.createBoardIterator();
    diceRoll(steps);

    MonopolyGameFixture game;
    game.turn(*playerFirst, startPossitionPlayerFirst);
    game.turn(*playerSecond, startPossitionPlayerSecond);

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
    auto possitionMarek = board.createBoardIterator();
    auto possitionDawid = board.createBoardIterator();
    diceRoll(steps);

    MonopolyGameFixture game;
    game.turn(*playerFirst, possitionMarek);
    game.turn(*playerSecond, possitionDawid);

    diceRoll(steps + 1);
    game.turn(*playerFirst, possitionMarek);
    game.turn(*playerSecond, possitionDawid);

    auto statusPlayerFirst = playerFirst->status();
    auto statusPlayerSecond = playerSecond->status();

    const auto expectedMoneyForPlayerFirst = moneyOnStartGame - BEAR_PRICE - PUB_PRICE + BEAR_RENT + (PUB_RENT * 2);
    EXPECT_EQ(statusPlayerFirst.money(), expectedMoneyForPlayerFirst);

    const auto expectedMoneyForPlayerSecond = moneyOnStartGame - BEAR_RENT - (PUB_RENT * 2);
    EXPECT_EQ(statusPlayerSecond.money(), expectedMoneyForPlayerSecond);
}

TEST_F(PropertyTestSuite, DawidShouldPayRentWhenMarekHaveTwoHousesOnBearProperty)
{
    unsigned int steps = 1;
    unsigned int stepsInSecondTrun = 2;
    unsigned int pubPropertyBuildingMode = 0;
    unsigned int numberOfHousesToBuy = 2;
    auto possitionMarek = board.createBoardIterator();
    auto possitionDawid = board.createBoardIterator();

    EXPECT_CALL(dice, diceThrow())
        .Times(4)
        .WillOnce(::testing::Return(steps))
        .WillOnce(::testing::Return(steps))
        .WillOnce(::testing::Return(stepsInSecondTrun))
        .WillOnce(::testing::Return(stepsInSecondTrun));

    MonopolyGameFixture game;
    game.turn(*playerFirst, possitionMarek);
    game.turn(*playerSecond, possitionDawid);

    game.turn(*playerFirst, possitionMarek);
    buildingModes[pubPropertyBuildingMode]->buyHouse(numberOfHousesToBuy, *playerFirst);
    game.turn(*playerSecond, possitionDawid);

    auto statusMarek = playerFirst->status();
    auto statusDawid = playerSecond->status();

    const auto expectedMoneyForMarek = moneyOnStartGame - BEAR_PRICE + BEAR_RENT - PUB_PRICE - (HOUSE_PRICE * 2) +
        PUB_RENT_BUILDING.at(numberOfHousesToBuy);
    EXPECT_EQ(statusMarek.money(), expectedMoneyForMarek);

    const auto expectedMoneyForDawid = moneyOnStartGame - BEAR_RENT - PUB_RENT_BUILDING.at(numberOfHousesToBuy);
    EXPECT_EQ(statusDawid.money(), expectedMoneyForDawid);
}

TEST_F(PropertyTestSuite, DawidShouldPayRentx2WhenMarekHaveTwoHousesOnBearPropertyAndSellIt)
{
    unsigned int steps = 1;
    unsigned int stepsInSecondTrun = 2;
    unsigned int pubPropertyBuildingMode = 0;
    unsigned int numberOfHousesToBuy = 2;
    auto possitionMarek = board.createBoardIterator();
    auto possitionDawid = board.createBoardIterator();

    EXPECT_CALL(dice, diceThrow())
        .Times(6)
        .WillOnce(::testing::Return(steps))
        .WillOnce(::testing::Return(steps))
        .WillOnce(::testing::Return(stepsInSecondTrun))
        .WillOnce(::testing::Return(stepsInSecondTrun))
        .WillOnce(::testing::Return(steps))
        .WillOnce(::testing::Return(3));

    MonopolyGameFixture game;
    game.turn(*playerFirst, possitionMarek);
    game.turn(*playerSecond, possitionDawid);

    game.turn(*playerFirst, possitionMarek);
    buildingModes[pubPropertyBuildingMode]->buyHouse(numberOfHousesToBuy, *playerFirst);
    game.turn(*playerSecond, possitionDawid);

    game.turn(*playerFirst, possitionMarek);
    buildingModes[pubPropertyBuildingMode]->sellHouse(numberOfHousesToBuy, *playerFirst);
    game.turn(*playerSecond, possitionDawid);

    auto statusMarek = playerFirst->status();
    auto statusDawid = playerSecond->status();

    const auto expectedMoneyForMarek = moneyOnStartGame - BEAR_PRICE + BEAR_RENT - PUB_PRICE - (HOUSE_PRICE * 2) +
        PUB_RENT_BUILDING.at(numberOfHousesToBuy) + HOUSE_PRICE + (PUB_RENT * 2);
    EXPECT_EQ(statusMarek.money(), expectedMoneyForMarek);

    const auto expectedMoneyForDawid =
        moneyOnStartGame - BEAR_RENT - PUB_RENT_BUILDING.at(numberOfHousesToBuy) - (PUB_RENT * 2);
    EXPECT_EQ(statusDawid.money(), expectedMoneyForDawid);
}
