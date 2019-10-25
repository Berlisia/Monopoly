#include "guest.h"

class GuestMock: public Guest
{
public:
    MOCK_METHOD1(lockInPrison, void(Squers::iterator));
    MOCK_METHOD1(withdrawMoney, unsigned int(unsigned int));
    MOCK_METHOD1(addMoney, void(unsigned int));
    MOCK_METHOD1(wantBuyProperty, void(unsigned int));
    MOCK_METHOD0(myName, const std::string&());
};
