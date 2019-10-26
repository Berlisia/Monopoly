#pragma once

#include "die.h"
#include "stateMachine.h"
#include "guest.h"

namespace
{
const unsigned int moneyOnStartGame = 1500;
}

class Property;

struct PlayerStatus
{
    BoardIterator actualPossisionOnBoard;
    unsigned int money;
    std::vector<Property*> propertis;
};

class Player : public StateMachine, public Guest
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice);

    void turn();

    void move();
    void lockInPrison(Squers::iterator prison) override;

    unsigned int withdrawMoney(unsigned int money) override;
    void addMoney(unsigned int money) override;
    bool wantBuyProperty(unsigned int price) override;

    const std::string& myName() override;
    void printStatus();
    const PlayerStatus status();

    void stateTransition(std::unique_ptr<State> state) override;

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    const Dice& dice;

    std::vector<Property*> propertis;
    unsigned int money = moneyOnStartGame;

    void moveNextSquare();
    Square* actualSquare();
    void walkThrought(unsigned int valueOfSteps);
    void actionOnWalkThrought();
    void actionOnStop();
};
