#include <gtest/gtest.h>

#include "../Tests/Mocks/DistrictMock.h"
#include "../Tests/Mocks/guestmock.h"

#include "BuildingProperty/BuildingPropertyFsm.h"

namespace  {
constexpr unsigned int PUB_PRICE = 100;
const std::string PUB_NAME = "Karczma 7 kotow";
const RentAtNumberOfBuildings PUB_RENT_BUILDING = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
constexpr Rent PUB_RENT = 5;
constexpr unsigned int PUB_MORTGAGE_PRICE = 50;

constexpr unsigned int HOUSE_PRICE = 10;
constexpr unsigned int HOTEL_PRICE = 50;
}

class BuildingPropertyFsmTestSuite : public ::testing::Test
{
public:
    BuildingPropertyFsmTestSuite():
        sut(card, district){}

    const CardInfo card = {PUB_RENT, PUB_RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE, PUB_MORTGAGE_PRICE};
    ::testing::NiceMock<DistrictMock> district;
    ::testing::NiceMock<GuestMock> owner;
    BuildingPropertyFsm sut;

    Rent rent(const Event& event)
    {
        return std::get<PayRent>(event).rentToPay;
    }
};

TEST_F(BuildingPropertyFsmTestSuite, WithoutOwner_PayRentEventShouldReturnZero)
{
    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), 0);
}


struct BuildingPropertyFsmDefault: public BuildingPropertyFsmTestSuite
{
    BuildingPropertyFsmDefault()
    {
        Event newOwnerE = NewOwner{&owner};
        sut.dispatch(newOwnerE);
    }
};

TEST_F(BuildingPropertyFsmDefault, PayRentEventShouldReturnPubRent)
{
    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT);
}

TEST_F(BuildingPropertyFsmDefault, PayRentShouldNotChangeWhenBuyFirstHouse)
{
    Event buyHouseE = BuyHause{1};
    Event payRentE = PayRent{};

    sut.dispatch(buyHouseE);
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT);
}

TEST_F(BuildingPropertyFsmDefault, PayRentShoulReturnZeroWhenGetMortgage)
{
    Event mortgageE = GetMortgage{};
    Event payRentE = PayRent{};

    sut.dispatch(mortgageE);
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), 0);
}

struct BuildingPropertyFsmAllPropertis: public BuildingPropertyFsmDefault
{
    BuildingPropertyFsmAllPropertis()
    {
        Event haveAllPropertisE = HaveAllPropertis{};
        sut.dispatch(haveAllPropertisE);
    }
};

TEST_F(BuildingPropertyFsmAllPropertis, PayRentEventShouldReturn2xPubRent)
{
    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT * 2);
}

TEST_F(BuildingPropertyFsmAllPropertis, PayRentShouldReturn2xPubRentAfterTryBuingMoreThanFourHouses)
{
    Event buyHousesE = BuyHause{5};
    Event payRentE = PayRent{};

    sut.dispatch(buyHousesE);
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT * 2);
}

TEST_F(BuildingPropertyFsmAllPropertis, PayRentShouldChangeWhenBuyFirstHouse)
{
    Event buyHouseE = BuyHause{1};
    Event payRentE = PayRent{};

    sut.dispatch(buyHouseE);
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(1));
}

struct BuildingPropertyFsmHousesBuilding: public BuildingPropertyFsmAllPropertis
{
    BuildingPropertyFsmHousesBuilding()
    {
        EXPECT_CALL(owner, withdrawMoney(HOUSE_PRICE)).WillOnce(::testing::Return(true));
        Event housesE = BuyHause{1};
        sut.dispatch(housesE);
    }

    void buyHouses(unsigned int numberOfHousesToBuy)
    {
        Event buyHouses = BuyHause{numberOfHousesToBuy};
        EXPECT_CALL(owner, withdrawMoney(HOUSE_PRICE * numberOfHousesToBuy)).WillOnce(::testing::Return(true));
        sut.dispatch(buyHouses);
    }
};

TEST_F(BuildingPropertyFsmHousesBuilding, PayRentEventShouldReturnRentForOneHouse)
{
    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(1));
}

TEST_F(BuildingPropertyFsmHousesBuilding, OwnerShouldPayForBuyHouses)
{
    const auto numberOfHousesToBuy = 2;
    Event buyHouses = BuyHause{numberOfHousesToBuy};

    EXPECT_CALL(owner, withdrawMoney(HOUSE_PRICE * numberOfHousesToBuy)).WillOnce(::testing::Return(true));
    sut.dispatch(buyHouses);
}

TEST_F(BuildingPropertyFsmHousesBuilding, PayRentEventShouldReturnRentForThreeHouses)
{
    const auto numberOfHousesToBuy = 2;
    buyHouses(numberOfHousesToBuy);

    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(3));
}

TEST_F(BuildingPropertyFsmHousesBuilding, PayRentEventShouldReturnRentForFourHouses)
{
    const auto numberOfHousesToBuy = 3;
    buyHouses(numberOfHousesToBuy);

    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(4));
}

TEST_F(BuildingPropertyFsmHousesBuilding, PayRentShouldNotChangeWhenOwnerTryToBuyHotelAndHaveNotFourHouses)
{
    Event buyHotelE = BuyHotel{};
    Event payRentE = PayRent{};

    sut.dispatch(buyHotelE);
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(1));
}

struct BuildingPropertyFsmHotel: public BuildingPropertyFsmHousesBuilding
{
    BuildingPropertyFsmHotel()
    {
        buyHouses(3);
        Event hotelE = BuyHotel{};
        EXPECT_CALL(owner, withdrawMoney(HOTEL_PRICE)).WillOnce(::testing::Return(true));
        sut.dispatch(hotelE);
    }
};

TEST_F(BuildingPropertyFsmHotel, PayRentShouldReturnRentForHotel)
{
    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(5));
}

TEST_F(BuildingPropertyFsmHotel, PayRentShouldNotChangeWhenOwnerTryBuyNextHotel)
{
    Event tryBuyHotel = BuyHotel{};
    Event payRentE = PayRent{};

    EXPECT_CALL(owner, withdrawMoney(HOTEL_PRICE)).Times(0);

    sut.dispatch(tryBuyHotel);
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), PUB_RENT_BUILDING.at(5));
}



