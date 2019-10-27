#include <gtest/gtest.h>

#include "Mocks/dicemock.h"
#include "Square/property.h"
#include "player.h"

namespace{
constexpr unsigned int PUB_PRICE = 100;
constexpr unsigned int PUB_RENT = 10;
const std::string PUB_NAME = "Karczma 7 kotow";
constexpr unsigned int EXPENSIVE_PRICE = 500;
constexpr unsigned int EXPENSIVE_RENT = 100;
const std::string EXPENSIVE_NAME = "Zimorodek";
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

    ::testing::NiceMock<Dice> dice;
    std::unique_ptr<Player> playerFirst;
    std::unique_ptr<Player> playerSecond;
    Squers propertisSut;

    void setupTestBoard();
};

void PropertyTestSuite::setupTestBoard()
{
    propertisSut.push_back(std::make_unique<Property>(PUB_PRICE, PUB_RENT, PUB_NAME));
    propertisSut.push_back(std::make_unique<Property>(EXPENSIVE_PRICE, EXPENSIVE_RENT, EXPENSIVE_NAME));
}
