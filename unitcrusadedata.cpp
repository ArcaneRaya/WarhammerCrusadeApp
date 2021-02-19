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

    this->battlesPlayed = 0;
    this->battlesSurvived = 0;
    this->enemyUnitsDestroyed = 0;
    this->enemyUnitsDestroyedPsychic = 0;
    this->enemyUnitsDestroyedRanged = 0;
    this->enemyUnitsDestroyedMelee = 0;

    this->markedForGreatnessTally = 0;
}
