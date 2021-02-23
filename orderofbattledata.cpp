#include <QDebug>
#include "orderofbattledata.h"

OrderOfBattleData::OrderOfBattleData()
{
    this->battleTally = 0;
    this->battlesWon = 0;
    this->requisitionPoints = 0;
    this->supplyLimit = 0;
}

void OrderOfBattleData::SetUnsaved()
{
    hasUnsavedChanges = true;
}

bool OrderOfBattleData::HasUnsavedChanges()
{
    bool hasAnyUnitUnsavedChanges = false;
    for(auto unit : units){
        if (unit.HasUnsavedChanges()){
            hasAnyUnitUnsavedChanges = true;
            break;
        }
    }
    return hasAnyUnitUnsavedChanges || hasUnsavedChanges;
}

void OrderOfBattleData::SetSaved()
{
    qDebug() << "SETSAVED called";

    hasUnsavedChanges = false;

    for(auto unit : units){
        unit.SetSaved();
    }

    qDebug() << HasUnsavedChanges();
    qDebug() << "SETSAVED ended";
}
