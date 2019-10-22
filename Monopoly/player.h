#pragma once
#include <string>

#include "die.h"
#include "board.h"
#include "stateMachine.h"

class Player : public StateMachine
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator);

    void turn();

    void lockInPrison();
    void moveOn(unsigned int valueOfSteps);
    unsigned int throwDice();

    unsigned int withdrawMoney(unsigned int money);
    void addMoney(unsigned int money);
    bool wantBuyProperty(unsigned int price);

    bool comparePlayer(const Player& player);

    void printStatus();
    const std::string& myName();

    void stateTransition(std::unique_ptr<State> state) override;

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    Dice dice;

    unsigned int money = 1000;

    Square* moveNextSquare();
};
