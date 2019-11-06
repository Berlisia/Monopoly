#include "estate.h"

bool Estate::operator ==(const Estate &e) const
{
    return name == e.name;
}

bool Estate::operator !=(const Estate &e) const
{
    return name != e.name;
}
