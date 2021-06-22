#ifndef BATTLEFIELDROLEDATA_H
#define BATTLEFIELDROLEDATA_H

#include <string>
#include "json.hpp"

class BattlefieldRoleData
{
public:
    BattlefieldRoleData();
    std::string name;
    int index;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
            BattlefieldRoleData,
            name,
            index)
};

#endif // BATTLEFIELDROLEDATA_H
