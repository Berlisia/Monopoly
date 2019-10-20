#pragma once
#include <string>

#include "die.h"
#include "board.h"
#include "event.h"
#include "stateMachine.h"

typedef std::unique_ptr<State> State_ptr;

class Player : public StateMachine
{
public:
    Player(std::string p_name, BoardIterator p_boardIterator);

    Square* moveNextSquare();
    unsigned int throwDice();
    void lockInPrison();

    unsigned int withdrawMoney(unsigned int money);
    void addMoney(unsigned int money);

    bool comparePlayer(const Player& player);
    bool wantBuyProperty(unsigned int price);

    void printStatus();
    const std::string& myName();

protected:
    void stateTransition(State *state);

private:
    std::string name;
    BoardIterator actualPossisionOnBoard;
    Dice dice;

    const State_ptr active;
    const State_ptr inPrisone;
    const State_ptr bancrut;

    Square* moveNextSquareInStateActive();
    Square* moveNextSquareDefault();

    unsigned int throwDiceInStateActive();
    unsigned int throwDiceInStatePrisone();
    unsigned int throwDiceInStateBancrut();

    unsigned int numberOfSkipedTurns = 0;
    unsigned int result = 1000;

};
