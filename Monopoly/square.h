#pragma once

class Square
{
public:
    Square() {}
    virtual ~Square() {}

    virtual int actionOnStop() const = 0;
    virtual unsigned int getPossition() const = 0;
    virtual int actionOnWalkThrought() const = 0;
};

