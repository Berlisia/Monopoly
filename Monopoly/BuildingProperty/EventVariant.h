#pragma once
#include <variant>

#include "guest.h"

struct NewOwner{ Guest* owner = nullptr; };
struct SellToBank{};

struct BuyHotel{};
struct SellHotel{};
struct BuyHause{ const unsigned int numHousesToBuy = 0; };
struct SellHouse{ const unsigned int numHousesToSell = 0; };
struct GetMortgage{};
struct RelieveMortgage{};

struct HaveAllPropertis{};
struct HaveNotAllPropertis{};

struct PayRent{ unsigned int rentToPay = 0; };

using Event = std::variant<SellToBank, NewOwner, BuyHotel, SellHotel, BuyHause, SellHouse, GetMortgage, RelieveMortgage,
                           PayRent, HaveNotAllPropertis, HaveAllPropertis>;
