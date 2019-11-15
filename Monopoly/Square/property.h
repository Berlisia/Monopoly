#pragma once
#include <memory>

#include "square.h"
#include "estate.h"
#include "rentpaymode.h"
#include "district.h"

class Player;

class Property: public Square, public Estate
{
public:
    Property(unsigned int p_price, std::unique_ptr<RentPayMode> p_rent,
             const District& p_district, const std::string p_name, Guest& p_owner):
        Estate(p_name),
        price(p_price),
        payRentMode(std::move(p_rent)),
        district(p_district),
        owner(&p_owner){}

    void actionOnStop(Guest&) override;
    void actionOnWalkThrought(Guest&) override;
    const std::string squareName() override;

    const std::string& estateName() const override;

private:
    unsigned int price;
    std::unique_ptr<RentPayMode> payRentMode;
    const District& district;
    Guest* owner;

    void buyPropertyByNewOwner(Guest& player);
};
