#include <gmock/gmock.h>

#include "Player.h"

class PlayerMock : public Player {
public:
  PlayerMock(std::string p_name, BoardIterator p_boardIterator,
             const Dice &p_dice,
             const SubjectBuildingProperty &p_buildingProperty)
      : Player(p_name, p_boardIterator, p_dice, p_buildingProperty) {}

  MOCK_METHOD0(move, void());

  MOCK_METHOD0(lockInPrison, void());
  MOCK_METHOD1(withdrawMoney, bool(unsigned int));
  MOCK_METHOD1(addMoney, void(unsigned int));
  MOCK_METHOD1(wantBuyProperty, bool(unsigned int));
  MOCK_METHOD0(myName, const std::string &());
};
