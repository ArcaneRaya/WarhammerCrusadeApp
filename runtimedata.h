#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QString>
#include "generalcrusadedata.h"
#include "orderofbattledata.h"

class RuntimeData
{
public:
    RuntimeData();
    GeneralCrusadeData * generalData;
    OrderOfBattleData * orderOfBattleData;
    QString filePathCurrentOrderOfBattle;
    bool currentOrderOfBattleHasUnsavedChanges = false;
};

#endif // RUNTIMEDATA_H
