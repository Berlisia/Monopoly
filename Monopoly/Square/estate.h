#pragma once
#include <string>

class Estate
{
public:
    Estate(const std::string p_name): name(p_name) {}
    virtual ~Estate() = default;

    virtual const std::string& estateName() = 0;

    bool operator == (const Estate& e) const
    {
        return name == e.name;
    }

protected:
    const std::string name;
};
