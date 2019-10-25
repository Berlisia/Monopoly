#include "player.h"

class PlayerMock : public Player
{
public:
    PlayerMock(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice):
        Player(p_name, p_boardIterator, p_dice) {}

    MOCK_METHOD0(move, void());

    MOCK_METHOD01(lockInPrison, void(Squers::iterator));
    MOCK_METHOD01(withdrawMoney, unsigned int(unsigned int));
    MOCK_METHOD01(addMoney, void(unsigned int));
    MOCK_METHOD01(wantBuyProperty, void(unsigned int));
    MOCK_METHOD00(myName, const std::string&());
};
