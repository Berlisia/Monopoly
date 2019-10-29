#pragma once

#include "stateMachine.h"
#include "guest.h"
#include "playerStatus.h"

namespace{
const unsigned int moneyOnStartGame = 1500;
}

class Estate;
class Dice;

class Player : public StateMachine, public Guest
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice);

    void turn();

    void move();
    void lockInPrison(Squers::iterator prison) override;

    unsigned int withdrawMoney(unsigned int money) override;
    void addMoney(unsigned int money) override;
    bool buyProperty(unsigned int price, Estate* property) override;
    unsigned int checkPropertisInDistrict(const std::vector<Estate *>& propertisInDistrict) override;
    unsigned int rollDice() override;

    const std::string& myName() override;
    void printStatus();
    const PlayerStatus status();

    void stateTransition(std::unique_ptr<State> state) override;

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    const Dice& dice;

    std::vector<Estate*> propertis;
    unsigned int money = moneyOnStartGame;

    void moveNextSquare();
    Square* actualSquare();
    std::vector<Estate*>::iterator findInPropertis(Estate* property);
    void walkThrought(unsigned int valueOfSteps);
    void actionOnWalkThrought();
    void actionOnStop();
};
