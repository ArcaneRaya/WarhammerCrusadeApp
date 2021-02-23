#include <QtDebug>
#include "unitcrusadedata.h"

UnitCrusadeData::UnitCrusadeData()
{
    this->name = "New Unit";
    this->battleFieldRole = "HQ";

    this->powerRating = 0;
    this->experiencePoints = 0;
    this->crusadePoints = 0;

    this->enemyUnitsDestroyedPsychicBattleRound = 0;
    this->enemyUnitsDestroyedRangedBattleRound = 0;
    this->enemyUnitsDestroyedMeleeBattleRound = 0;
    this->agenda1TallyBattleRound = 0;
    this->agenda2TallyBattleRound = 0;
    this->agenda3TallyBattleRound = 0;

    this->rank = "BATTLE-READY";
    this->battlesPlayed = 0;
    this->battlesSurvived = 0;
    this->enemyUnitsDestroyedPsychic = 0;
    this->enemyUnitsDestroyedRanged = 0;
    this->enemyUnitsDestroyedMelee = 0;

    this->markedForGreatnessTally = 0;

    hasUnsavedChanges = false;
}

int UnitCrusadeData::GetEnemyUnitsDestroyedTotal()
{
    return enemyUnitsDestroyedMelee + enemyUnitsDestroyedPsychic + enemyUnitsDestroyedRanged;
}

int UnitCrusadeData::GetEnemyUnitsDestroyedBattleRoundTotal()
{
    return enemyUnitsDestroyedMeleeBattleRound + enemyUnitsDestroyedPsychicBattleRound + enemyUnitsDestroyedRangedBattleRound;
}

bool UnitCrusadeData::HasUnsavedChanges()
{
    if (hasUnsavedChanges){
        qDebug() << "has unsaved changes: " + QString::fromStdString(name);
    }
    return hasUnsavedChanges;
}

void UnitCrusadeData::SetUnsaved()
{
    qDebug() << "set unsaved " + QString::fromStdString(name);
    hasUnsavedChanges = true;
}

void UnitCrusadeData::SetSaved()
{
    qDebug() << "set saved " + QString::fromStdString(name);
    hasUnsavedChanges = false;
    if(hasUnsavedChanges){
        qDebug() << "somehow not set correctly " + QString::fromStdString(name);
    }
}
