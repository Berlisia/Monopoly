#include <gtest/gtest.h>

#include "DistrictMock.h"
#include "GuestMock.h"

#include "BuildingPropertyFsm.h"

namespace {
constexpr unsigned int PUB_PRICE = 100;
const std::string PUB_NAME = "Karczma 7 kotow";
const RentAtNumberOfBuildings PUB_RENT_BUILDING = {
    {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
constexpr Rent PUB_RENT = 5;
constexpr unsigned int PUB_MORTGAGE_PRICE = 50;

constexpr unsigned int HOUSE_PRICE = 10;
constexpr unsigned int HOTEL_PRICE = 50;
} // namespace

class BuildingPropertyFsmTestSuite : public ::testing::Test {
public:
  BuildingPropertyFsmTestSuite() : sut(card, district) {
    ON_CALL(district, propertis()).WillByDefault(::testing::ReturnRef(vec));
  }

  const CardInfo card = {PUB_RENT, PUB_RENT_BUILDING, HOUSE_PRICE, HOTEL_PRICE,
                         PUB_MORTGAGE_PRICE};
  ::testing::NiceMock<DistrictMock> district;
  ::testing::StrictMock<GuestMock> owner;
  BuildingPropertyFsm sut;
  std::vector<const Estate *> vec = {};

  Rent rent(const Event &event) { return std::get<PayRent>(event).rentToPay; }

  void checkRent(unsigned int expectedRent) {
    Event payRentE = PayRent{};
    sut.dispatch(payRentE);
    EXPECT_EQ(rent(payRentE), expectedRent);
  }
};

TEST_F(BuildingPropertyFsmTestSuite,
       WithoutOwner_PayRentEventShouldReturnZero) {
  unsigned int expectedRent = 0;
  checkRent(expectedRent);
}

struct BuildingPropertyFsmDefault : public BuildingPropertyFsmTestSuite {
  BuildingPropertyFsmDefault() {
    Event newOwnerE = NewOwner{&owner};
    sut.dispatch(newOwnerE);
  }
};

TEST_F(BuildingPropertyFsmDefault, PayRentEventShouldReturnPubRent) {
  checkRent(PUB_RENT);
}

TEST_F(BuildingPropertyFsmDefault, PayRentShouldNotChangeWhenBuyFirstHouse) {
  Event buyHouseE = BuyHause{1};
  sut.dispatch(buyHouseE);
  checkRent(PUB_RENT);
}

TEST_F(BuildingPropertyFsmDefault, PayRentShoulReturnZeroWhenGetMortgage) {
  Event mortgageE = GetMortgage{};
  EXPECT_CALL(owner, addMoney(card.mortgagePrice));

  sut.dispatch(mortgageE);
  checkRent(0);
}

TEST_F(BuildingPropertyFsmDefault,
       shouldChangeRentAfterHandleHaveAllPropertis) {
  checkRent(PUB_RENT);

  Event haveAllPropertisE = HaveAllPropertis{};
  sut.dispatch(haveAllPropertisE);
  checkRent(PUB_RENT * 2);
}

TEST_F(BuildingPropertyFsmDefault, shouldNotChangeRentWhenNewOwner) {
  checkRent(PUB_RENT);
  ::testing::StrictMock<GuestMock> nextOwner;
  Event newOwnerE = NewOwner{&nextOwner};
  sut.dispatch(newOwnerE);
  checkRent(PUB_RENT);
}

TEST_F(BuildingPropertyFsmDefault,
       shouldAddMoneyForSecondOwnerAfterChangeOwner) {
  ::testing::StrictMock<GuestMock> nextOwner;
  Event newOwnerE = NewOwner{&nextOwner};
  sut.dispatch(newOwnerE);

  EXPECT_CALL(nextOwner, addMoney(card.mortgagePrice));
  Event mortgageE = GetMortgage{};
  sut.dispatch(mortgageE);
}

TEST_F(BuildingPropertyFsmDefault, shouldDeleteOwner) {
  Event sellToBankE = SellToBank{};
  sut.dispatch(sellToBankE);

  EXPECT_CALL(owner, addMoney(card.mortgagePrice)).Times(0);
  Event mortgageE = GetMortgage{};
  sut.dispatch(mortgageE);
}

struct BuildingPropertyFsmAllPropertis : public BuildingPropertyFsmDefault {
  BuildingPropertyFsmAllPropertis() {
    Event haveAllPropertisE = HaveAllPropertis{};
    sut.dispatch(haveAllPropertisE);
  }
};

TEST_F(BuildingPropertyFsmAllPropertis,
       PayRentShouldReturn2xPubRentAfterTryBuingMoreThanFourHouses) {
  Event buyHousesE = BuyHause{5};

  sut.dispatch(buyHousesE);
  checkRent(PUB_RENT * 2);
}

TEST_F(BuildingPropertyFsmAllPropertis, PayRentShouldChangeWhenBuyFirstHouse) {
  Event buyHouseE = BuyHause{1};
  EXPECT_CALL(owner, withdrawMoney(card.housePrice))
      .WillOnce(::testing::Return(true));

  sut.dispatch(buyHouseE);
  checkRent(PUB_RENT_BUILDING.at(1));
}

TEST_F(BuildingPropertyFsmAllPropertis, PayRentShoulReturnZeroWhenGetMortgage) {
  Event mortgageE = GetMortgage{};
  EXPECT_CALL(owner, addMoney(card.mortgagePrice));

  sut.dispatch(mortgageE);
  checkRent(0);
}

TEST_F(BuildingPropertyFsmAllPropertis,
       rentShouldChangeAfterHandleNotAllPropertis) {
  Event notAllPropE = HaveNotAllPropertis{};
  sut.dispatch(notAllPropE);
  checkRent(PUB_RENT);
}

TEST_F(BuildingPropertyFsmAllPropertis,
       shouldAddMoneyForSecondOwnerAfterChangeOwner) {
  ::testing::StrictMock<GuestMock> nextOwner;
  Event newOwnerE = NewOwner{&nextOwner};
  sut.dispatch(newOwnerE);

  EXPECT_CALL(nextOwner, addMoney(card.mortgagePrice));
  Event mortgageE = GetMortgage{};
  sut.dispatch(mortgageE);
}

TEST_F(BuildingPropertyFsmAllPropertis, shouldDeleteOwner) {
  Event sellToBankE = SellToBank{};
  sut.dispatch(sellToBankE);

  EXPECT_CALL(owner, addMoney(card.mortgagePrice)).Times(0);
  Event mortgageE = GetMortgage{};
  sut.dispatch(mortgageE);
}

struct BuildingPropertyFsmHousesBuilding
    : public BuildingPropertyFsmAllPropertis {
  BuildingPropertyFsmHousesBuilding() {
    EXPECT_CALL(owner, withdrawMoney(HOUSE_PRICE))
        .WillOnce(::testing::Return(true));
    Event housesE = BuyHause{1};
    sut.dispatch(housesE);
  }

  void buyHouses(unsigned int numberOfHousesToBuy) {
    Event buyHouses = BuyHause{numberOfHousesToBuy};
    EXPECT_CALL(owner, withdrawMoney(HOUSE_PRICE * numberOfHousesToBuy))
        .WillOnce(::testing::Return(true));
    sut.dispatch(buyHouses);
  }
};

TEST_F(BuildingPropertyFsmHousesBuilding,
       PayRentEventShouldReturnRentForOneHouse) {
  checkRent(PUB_RENT_BUILDING.at(1));
}

TEST_F(BuildingPropertyFsmHousesBuilding, OwnerShouldPayForBuyHouses) {
  const auto numberOfHousesToBuy = 2;
  Event buyHouses = BuyHause{numberOfHousesToBuy};

  EXPECT_CALL(owner, withdrawMoney(HOUSE_PRICE * numberOfHousesToBuy))
      .WillOnce(::testing::Return(true));
  sut.dispatch(buyHouses);
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       PayRentEventShouldReturnRentForThreeHouses) {
  const auto numberOfHousesToBuy = 2;
  buyHouses(numberOfHousesToBuy);

  checkRent(PUB_RENT_BUILDING.at(3));
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       PayRentEventShouldReturnRentForFourHouses) {
  const auto numberOfHousesToBuy = 3;
  buyHouses(numberOfHousesToBuy);
  checkRent(PUB_RENT_BUILDING.at(4));
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       PayRentShouldNotChangeWhenOwnerTryToBuyHotelAndHaveNotFourHouses) {
  Event buyHotelE = BuyHotel{};
  sut.dispatch(buyHotelE);
  checkRent(PUB_RENT_BUILDING.at(1));
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       OwnerShouldSellAllHousesWhenGetMortage) {
  const auto numberOfHousesToBuy = 2;
  buyHouses(numberOfHousesToBuy);
  EXPECT_CALL(owner, addMoney((numberOfHousesToBuy + 1) * card.housePrice / 2));
  EXPECT_CALL(owner, addMoney(card.mortgagePrice));

  Event mortgage = GetMortgage{};
  sut.dispatch(mortgage);
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       OwnerShouldGetMoneyWhenSellSomeHouses) {
  const auto numberOfHousesToBuy = 2;
  buyHouses(numberOfHousesToBuy);

  EXPECT_CALL(owner, addMoney(card.housePrice / 2));

  Event sellHouse = SellHouse{1};
  sut.dispatch(sellHouse);
  checkRent(PUB_RENT_BUILDING.at(2));
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       OwnerShouldGetMoneyWhenSellAllHouses_payRentShouldChangeTo2xRent) {
  const auto numberOfHousesToBuy = 1;
  buyHouses(numberOfHousesToBuy);

  EXPECT_CALL(owner, addMoney(card.housePrice / 2 * (numberOfHousesToBuy + 1)));

  Event sellHouse = SellHouse{numberOfHousesToBuy + 1};
  sut.dispatch(sellHouse);
  checkRent(card.rent * 2);
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       rentShouldChangeAfterHandleNotAllPropertis) {
  Event notAllPropE = HaveNotAllPropertis{};

  EXPECT_CALL(owner, addMoney(card.housePrice / 2));
  sut.dispatch(notAllPropE);

  checkRent(PUB_RENT);
}

TEST_F(BuildingPropertyFsmHousesBuilding,
       shouldAddMoneyForSecondOwnerAfterChangeOwner) {
  ::testing::StrictMock<GuestMock> nextOwner;
  Event newOwnerE = NewOwner{&nextOwner};
  Event mortgageE = GetMortgage{};

  EXPECT_CALL(owner, addMoney(card.housePrice / 2));
  sut.dispatch(newOwnerE);

  EXPECT_CALL(nextOwner, addMoney(card.mortgagePrice));
  sut.dispatch(mortgageE);
}

TEST_F(BuildingPropertyFsmHousesBuilding, shouldDeleteOwner) {
  Event sellToBankE = SellToBank{};
  Event mortgageE = GetMortgage{};

  EXPECT_CALL(owner, addMoney(card.housePrice / 2));
  EXPECT_CALL(owner, addMoney(card.mortgagePrice)).Times(0);
  sut.dispatch(sellToBankE);
  sut.dispatch(mortgageE);
}

struct BuildingPropertyFsmHotel : public BuildingPropertyFsmHousesBuilding {
  BuildingPropertyFsmHotel() {
    buyHouses(3);
    Event hotelE = BuyHotel{};
    EXPECT_CALL(owner, addMoney(card.housePrice / 2 * 4));
    EXPECT_CALL(owner, withdrawMoney(HOTEL_PRICE))
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(owner, withdrawMoney(card.housePrice / 2 * 4))
        .WillOnce(::testing::Return(true));
    sut.dispatch(hotelE);
  }
};

TEST_F(BuildingPropertyFsmHotel, PayRentShouldReturnRentForHotel) {
  checkRent(PUB_RENT_BUILDING.at(5));
}

TEST_F(BuildingPropertyFsmHotel,
       PayRentShouldNotChangeWhenOwnerTryBuyNextHotel) {
  Event tryBuyHotel = BuyHotel{};
  EXPECT_CALL(owner, withdrawMoney(HOTEL_PRICE)).Times(0);

  sut.dispatch(tryBuyHotel);
  checkRent(PUB_RENT_BUILDING.at(5));
}

TEST_F(BuildingPropertyFsmHotel,
       OwnerShouldGetMoneyForMortgageAndAllBuildingsWhenGetMortgage) {
  Event mortgageE = GetMortgage{};

  EXPECT_CALL(owner, addMoney(HOTEL_PRICE / 2));
  EXPECT_CALL(owner, addMoney(HOUSE_PRICE / 2 * 4));
  EXPECT_CALL(owner, addMoney(card.mortgagePrice));

  sut.dispatch(mortgageE);
  checkRent(0);
}

TEST_F(BuildingPropertyFsmHotel,
       OwnerShouldGetAllMoneyForBuildingWhenSellHotel) {
  Event sellHotelE = SellHotel{};

  EXPECT_CALL(owner, addMoney(HOTEL_PRICE / 2));
  EXPECT_CALL(owner, addMoney(HOUSE_PRICE / 2 * 4));

  sut.dispatch(sellHotelE);
  checkRent(card.rent * 2);
}

TEST_F(BuildingPropertyFsmHotel, rentShouldChangeAfterHandleNotAllPropertis) {
  Event notAllPropE = HaveNotAllPropertis{};

  EXPECT_CALL(owner, addMoney(HOTEL_PRICE / 2));
  EXPECT_CALL(owner, addMoney(HOUSE_PRICE / 2 * 4));
  sut.dispatch(notAllPropE);

  checkRent(PUB_RENT);
}

TEST_F(BuildingPropertyFsmHotel, shouldAddMoneyForSecondOwnerAfterChangeOwner) {
  ::testing::StrictMock<GuestMock> nextOwner;
  Event newOwnerE = NewOwner{&nextOwner};
  Event mortgageE = GetMortgage{};

  EXPECT_CALL(owner, addMoney(HOTEL_PRICE / 2));
  EXPECT_CALL(owner, addMoney(HOUSE_PRICE / 2 * 4));
  sut.dispatch(newOwnerE);

  EXPECT_CALL(nextOwner, addMoney(card.mortgagePrice));
  sut.dispatch(mortgageE);
}

TEST_F(BuildingPropertyFsmHotel, shouldDeleteOwner) {
  Event sellToBankE = SellToBank{};
  Event mortgageE = GetMortgage{};

  EXPECT_CALL(owner, addMoney(HOTEL_PRICE / 2));
  EXPECT_CALL(owner, addMoney(HOUSE_PRICE / 2 * 4));
  EXPECT_CALL(owner, addMoney(card.mortgagePrice)).Times(0);
  sut.dispatch(sellToBankE);
  sut.dispatch(mortgageE);
}

struct BuildingPropertyFsmMortgage : public BuildingPropertyFsmHotel {
  BuildingPropertyFsmMortgage() {
    Event mortgageE = GetMortgage{};
    EXPECT_CALL(owner, addMoney(HOTEL_PRICE / 2));
    EXPECT_CALL(owner, addMoney(HOUSE_PRICE / 2 * 4));
    EXPECT_CALL(owner, addMoney(card.mortgagePrice));
    sut.dispatch(mortgageE);
  }
};

TEST_F(BuildingPropertyFsmMortgage,
       ShouldPayOffDeptWhenReliveMortgageAndHaveAllPropertis) {
  auto morgagePrice =
      static_cast<unsigned int>(std::round(card.mortgagePrice * 1.1));
  EXPECT_CALL(owner, withdrawMoney(morgagePrice))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(owner, checkPropertisInDistrict(district.propertis()))
      .WillOnce(testing::Return(district.propertis().size()));

  Event reliveMortgage = RelieveMortgage{};
  sut.dispatch(reliveMortgage);
  checkRent(card.rent * 2);
}

TEST_F(BuildingPropertyFsmMortgage,
       ShouldPayOffDeptWhenReliveMortgageAndHaveNotAllPropertis) {
  auto morgagePrice =
      static_cast<unsigned int>(std::round(card.mortgagePrice * 1.1));
  auto badSize = 2;
  EXPECT_CALL(owner, withdrawMoney(morgagePrice))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(owner, checkPropertisInDistrict(district.propertis()))
      .WillOnce(testing::Return(badSize));

  Event reliveMortgage = RelieveMortgage{};
  sut.dispatch(reliveMortgage);
  checkRent(card.rent);
}

TEST_F(BuildingPropertyFsmMortgage, newOwnerShouldNotChangeMortgage) {
  ::testing::StrictMock<GuestMock> nextOwner;
  Event newOwnerE = NewOwner{&nextOwner};
  Event reliveMortgage = RelieveMortgage{};

  auto morgagePrice =
      static_cast<unsigned int>(std::round(card.mortgagePrice * 1.1));
  auto badSize = 2;

  EXPECT_CALL(nextOwner, withdrawMoney(morgagePrice))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(nextOwner, checkPropertisInDistrict(district.propertis()))
      .WillOnce(testing::Return(badSize));

  sut.dispatch(newOwnerE);
  sut.dispatch(reliveMortgage);
  checkRent(card.rent);
}
