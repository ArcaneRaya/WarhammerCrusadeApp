#ifndef GENERALCRUSADEDATA_H
#define GENERALCRUSADEDATA_H

#include <QString>
#include <QStringList>
#include <vector>
#include <string>
#include "json.hpp"
#include "battlefieldroledata.h"

class GeneralCrusadeData
{
public:
    GeneralCrusadeData();
    void GetBattlefieldRolesStringList(QStringList * list);
    std::vector<BattlefieldRoleData> roles;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE
    (
            GeneralCrusadeData,
            roles
    )
};

#endif // GENERALCRUSADEDATA_H
