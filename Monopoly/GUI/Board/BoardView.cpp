#include "BoardView.hpp"

void BoardView::addfield(std::string path, std::string name)
{
    fields.push_back(Field(path, name));
}
const std::vector<Field>& BoardView::getFields()
{
    return fields;
}