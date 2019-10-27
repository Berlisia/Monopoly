#pragma once

class Printer
{
public:
    virtual ~Printer() = default;
    virtual void update() = 0;
};
