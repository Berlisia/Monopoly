#pragma once

#include "die.h"
#include "board.h"
#include "stateMachine.h"
#include "guest.h"

class Property;

class Player : public StateMachine, public Guest
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator, const Dice& p_dice);

    void turn();

    void move();
    void lockInPrison();

    unsigned int withdrawMoney(unsigned int money);
    void addMoney(unsigned int money);
    bool wantBuyProperty(unsigned int price);
    const std::string& myName();

    void printStatus();

    void stateTransition(std::unique_ptr<State> state) override;

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    const Dice& dice;
    std::vector<Property*> propertis;

    unsigned int money = 1000;

    void moveNextSquare();
    Square* actualSquare();
    void walkThrought(unsigned int valueOfSteps);
    void actionOnWalkThrought();
    void actionOnStop();
};
