#ifndef ORDEROFBATTLEDATA_H
#define ORDEROFBATTLEDATA_H
#include <vector>
#include "unitcrusadedata.h"
#include "json.hpp"

class OrderOfBattleData
{
public:
    OrderOfBattleData();
    std::string name;
    std::string faction;

    int battleTally;
    int battlesWon;
    int requisitionPoints;
    int supplyLimit;

    std::vector<UnitCrusadeData> units;


    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
            OrderOfBattleData,
            name,
            faction,
            battleTally,
            battlesWon,
            requisitionPoints,
            supplyLimit,
            units
            )
};

#endif // ORDEROFBATTLEDATA_H
