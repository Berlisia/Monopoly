#pragma once
#include <vector>

//#include "Board.h"
#include "Field.hpp"

class BoardView
{
public:
    void addfield(std::string path, std::string name);
    const std::vector<Field>& getFields();

private:
    std::vector<Field> fields{};
};
