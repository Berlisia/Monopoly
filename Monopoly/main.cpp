#include <iostream>
#include <utility>

#include "Bankier.h"
#include "Board.h"
#include "BuildingProperty.h"
#include "Deposite.h"
#include "MonopolyGame.h"
#include "Penalty.h"
#include "Player.h"
#include "Prison.h"
#include "Property.h"
#include "RandomSquare.h"
#include "Reward.h"
#include "Square.h"
#include "Start.h"

#include <QApplication>
#include "GUI/MainWindow.h"

using namespace std;

namespace
{
int PRICE_FOR_START = 100;
int PRICE_FOR_PENALTY = 50;
int PRICE_FOR_REWARD = 20;
int NUMBER_OF_SQUERS = 40;
unsigned int PRICE_FOR_DEPOSITE = 5;
const RentAtNumberOfBuildings RENT_BUILDING = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
constexpr unsigned int HOUSE_PRICE = 10;
constexpr unsigned int HOTEL_PRICE = 50;
} // namespace

template <typename T, typename... Args>
std::unique_ptr<T> createSquare(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

void createRandomSquare(Squers& squares)
{
    Squers randomSquares;
    randomSquares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    randomSquares.push_back(createSquare<Penalty>(PRICE_FOR_PENALTY));
    randomSquares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    squares.push_back(createSquare<RandomSquare>(std::move(randomSquares)));
}

std::unique_ptr<Property> createBuildingProperty(
    CardInfo card,
    unsigned int price,
    const std::string name,
    const District& district,
    SubjectBuildingProperty& subjectBuildingProperty,
    std::vector<HouseDevelop*>& buildingModes,
    Bankier& bankier)
{
    auto buildingMode = std::make_unique<BuildingProperty>(card, district);
    buildingModes.push_back(buildingMode.get());
    subjectBuildingProperty.attach(buildingMode.get());
    return std::make_unique<Property>(price, std::move(buildingMode), district, name, bankier);
}

Squers createSimpleBoard(
    std::vector<District>& districts,
    std::vector<HouseDevelop*>& buildingModes,
    SubjectBuildingProperty& buildingPropertyNotify,
    Bankier& bankier)
{
    Squers squares;
    squares.push_back(createSquare<Start>(PRICE_FOR_START));
    auto property = createBuildingProperty(
        {10, RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE},
        100,
        "niedzwiedzia buda",
        districts[0],
        buildingPropertyNotify,
        buildingModes,
        bankier);
    districts[0].assignPropertyToDistrict(property.get());
    squares.push_back(std::move(property));
    squares.push_back(createSquare<Prison>());
    for (int i = 4; i < 10; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    }
    property = createBuildingProperty(
        {20, RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE},
        100,
        "Stara hata",
        districts[0],
        buildingPropertyNotify,
        buildingModes,
        bankier);
    districts[0].assignPropertyToDistrict(property.get());
    squares.push_back(std::move(property));
    createRandomSquare(squares);
    squares.push_back(createSquare<Deposite>(PRICE_FOR_DEPOSITE));
    squares.push_back(createSquare<Prison>());
    for (int i = 14; i < 20; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    }
    property = createBuildingProperty(
        {30, RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE},
        200,
        "Kocia kolyska",
        districts[1],
        buildingPropertyNotify,
        buildingModes,
        bankier);
    districts[1].assignPropertyToDistrict(property.get());
    squares.push_back(std::move(property));
    createRandomSquare(squares);
    squares.push_back(createSquare<Prison>());
    for (int i = 23; i < 30; i++)
    {
        squares.push_back(createSquare<Penalty>(PRICE_FOR_PENALTY));
    }
    property = createBuildingProperty(
        {40, RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE},
        300,
        "Karczma 7 kotow",
        districts[1],
        buildingPropertyNotify,
        buildingModes,
        bankier);
    districts[1].assignPropertyToDistrict(property.get());
    squares.push_back(std::move(property));
    createRandomSquare(squares);
    squares.push_back(createSquare<Prison>());
    for (int i = 33; i < NUMBER_OF_SQUERS; i++)
    {
        squares.push_back(createSquare<Reward>(PRICE_FOR_REWARD));
    }
    return squares;
}

Players createSomePlayers(BoardIterator board, const Dice& dice, const SubjectBuildingProperty& buildingPropertyNotify)
{
    Players players;
    players.push_back(std::make_unique<Player>("JANEK", board, dice, buildingPropertyNotify));
    players.push_back(std::make_unique<Player>("KRZYSIEK", board, dice, buildingPropertyNotify));
    return players;
}

int main(int argc, char* argv[])
{
    SubjectBuildingProperty buildingPropertyNotify;
    std::vector<District> districts;
    districts.push_back(District());
    districts.push_back(District());
    std::vector<HouseDevelop*> buildingModes;
    Bankier bankier;

    auto squares = createSimpleBoard(districts, buildingModes, buildingPropertyNotify, bankier);

    Board board(std::move(squares));
    Dice dice;
    auto players = createSomePlayers(board.createBoardIterator(), dice, buildingPropertyNotify);

    MonopolyGame game(std::move(board), std::move(players));
    game.startGame(10);

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
