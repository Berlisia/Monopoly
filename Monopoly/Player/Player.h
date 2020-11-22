#pragma once

#include "Contestant.h"
#include "PlayerFsm.h"
#include "PlayerPropertis.h"

namespace
{
const unsigned int moneyOnStartGame = 1500;
}

class Estate;
class Dice;

using Fsm = std::unique_ptr<FsmBase<PlayerState, PlayerEvent>>;

class Player : public Contestant
{
public:
    Player(std::string p_name, const Dice& p_dice, const SubjectBuildingProperty& p_buildingProperty);

    void turn() override;
    const PlayerStatus status() override;

    void lockInPrison() override;

    bool withdrawMoney(unsigned int money) override;
    bool haveEnoughtMoney(unsigned int money) override;
    void addMoney(unsigned int money) override;

    bool buyProperty(unsigned int price, const Estate* property, const District& district) override;
    void sellProperty(unsigned int price, const Estate* property, const District& district) override;
    unsigned int checkPropertisInDistrict(const std::vector<const Estate*>& propertisInDistrict) override;
    unsigned int rollDice() override;
    const std::string& myName() override;

    void printStatus();

private:
    std::string name;
    PlayerPropertis propertis;
    Fsm fsm;
    unsigned int money = moneyOnStartGame;

    const Dice& dice;
};
