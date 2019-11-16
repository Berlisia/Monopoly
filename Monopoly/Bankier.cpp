#include "bankier.h"

namespace {
const std::string NAME = "Bankier";
}

void Bankier::lockInPrison(Squers::iterator){

}

bool Bankier::withdrawMoney(unsigned int ){
    return false;
}

void Bankier::addMoney(unsigned int ){
}

bool Bankier::haveEnoughtMoney(unsigned int){
    return false;
}

bool Bankier::buyProperty(unsigned int, const Estate*, const District&){
    return false;
}

void Bankier::sellProperty(unsigned int, const Estate*, const District&){
}

unsigned int Bankier::checkPropertisInDistrict(const std::vector<const Estate *>&){
    return 0;
}

unsigned int Bankier::rollDice(){
    return 0;
}

const std::string& Bankier::myName(){
    return NAME;
}
