#ifndef ORDEROFBATTLEDATA_H
#define ORDEROFBATTLEDATA_H
#include <vector>
#include "unitcrusadedata.h"

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
};

#endif // ORDEROFBATTLEDATA_H
