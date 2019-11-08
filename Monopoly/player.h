#pragma once

#include "stateMachine.h"
#include "guest.h"
#include "playerStatus.h"
#include "Square/subjectbuildingproperty.h"

namespace{
const unsigned int moneyOnStartGame = 1500;
}

class Estate;
class Dice;

class Player : public StateMachine, public Guest
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice,
           const SubjectBuildingProperty& p_buildingProperty);

    void turn();

    void move();

    void lockInPrison(Squers::iterator prison) override;
    bool withdrawMoney(unsigned int money) override;
    void addMoney(unsigned int money) override;
    bool buyProperty(unsigned int price, const Estate* property, const District& district) override;
    unsigned int checkPropertisInDistrict(const std::vector<const Estate *>& propertisInDistrict) override;
    unsigned int rollDice() override;
    const std::string& myName() override;

    void printStatus();
    const PlayerStatus status();

    void stateTransition(std::unique_ptr<State> state) override;

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    const Dice& dice;
    const SubjectBuildingProperty& buildingProperty;

    std::vector<const Estate*> propertis;
    unsigned int money = moneyOnStartGame;

    void moveNextSquare();
    Square* actualSquare();
    std::vector<const Estate*>::iterator findInPropertis(const Estate* property);
    void walkThrought(unsigned int valueOfSteps);
    void actionOnWalkThrought();
    void actionOnStop();
    void notifyBuildingProperty(const District& district);
};
