#pragma once
#include <string>

class Estate
{
public:
    Estate(const std::string p_name): name(p_name) {}
    virtual ~Estate() = default;

    virtual const std::string& estateName() const = 0;
    bool operator == (const Estate& e) const;
    bool operator != (const Estate& e) const;

protected:
    const std::string name;
};
