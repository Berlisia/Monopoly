#pragma once

class Guest;

class RentPayMode
{
public:
    virtual ~RentPayMode() = default;
    virtual void payRent(Guest& player, Guest& owner) const = 0;
};
