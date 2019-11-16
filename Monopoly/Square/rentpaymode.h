#pragma once

class Guest;

class RentPayMode
{
public:
    virtual ~RentPayMode() = default;
    virtual void payRent(Guest& player) = 0;
    virtual void setNewOwner(Guest& owner) = 0;
};
