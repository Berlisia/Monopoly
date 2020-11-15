#pragma once

#include "Contestant.h"
#include "PlayerPropertis.h"
#include "StateMachine.h"

namespace {
const unsigned int moneyOnStartGame = 1500;
}

class Estate;
class Dice;

class Player : public StateMachine, public Contestant {
public:
  Player(std::string p_name, BoardIterator p_boardIterator, const Dice &p_dice,
         const SubjectBuildingProperty &p_buildingProperty);

  void turn() override;
  const PlayerStatus status() override;

  void lockInPrison() override;
  bool withdrawMoney(unsigned int money) override;
  bool haveEnoughtMoney(unsigned int money) override;
  void addMoney(unsigned int money) override;
  bool buyProperty(unsigned int price, const Estate *property,
                   const District &district) override;
  void sellProperty(unsigned int price, const Estate *property,
                    const District &district) override;
  unsigned int checkPropertisInDistrict(
      const std::vector<const Estate *> &propertisInDistrict) override;
  unsigned int rollDice() override;
  const std::string &myName() override;

  void stateTransition(std::unique_ptr<State> state) override;

  void printStatus();
  void move();

private:
  std::string name;
  BoardIterator actualPossisionOnBoard;
  PlayerPropertis propertis;
  unsigned int money = moneyOnStartGame;

  const Dice &dice;

  void moveNextSquare();
  Square *actualSquare();

  void walkThrought(unsigned int valueOfSteps);
  void actionOnWalkThrought();
  void actionOnStop();
  void notifyBuildingProperty(const District &district);
};
