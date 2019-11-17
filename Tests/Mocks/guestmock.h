#include <gmock/gmock.h>

#include "guest.h"

class GuestMock: public Guest
{
public:
    MOCK_METHOD1(lockInPrison, void(Squers::iterator));
    MOCK_METHOD1(withdrawMoney, bool(unsigned int));
    MOCK_METHOD1(addMoney, void(unsigned int));
    MOCK_METHOD1(wantBuyProperty, bool(unsigned int));
    MOCK_METHOD0(myName, const std::string&());
    MOCK_METHOD1(haveEnoughtMoney, bool(unsigned int));
    MOCK_METHOD3(buyProperty, bool(unsigned int, const Estate*, const District&));
    MOCK_METHOD3(sellProperty, void(unsigned int, const Estate* property, const District& district));
    MOCK_METHOD1(checkPropertisInDistrict, unsigned int(const std::vector<const Estate*>&));
    MOCK_METHOD0(rollDice, unsigned int());
};
