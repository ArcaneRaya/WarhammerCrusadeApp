#ifndef UNITCRUSADEDATA_H
#define UNITCRUSADEDATA_H

#include <string>
#include "json.hpp"

class UnitCrusadeData
{
public:
    UnitCrusadeData();

    // basic info
    std::string name;
    std::string battleFieldRole;
    std::string crusadeFaction;
    std::string selectableKeywords;
    std::string unitType;
    std::string equipment;
    std::string psychicPowers;
    std::string warlordTraits;
    std::string relics;
    std::string upgrades;

    // experience etc
    int powerRating;
    int experiencePoints;
    int crusadePoints;

    // combat tallies
    int battlesPlayed;
    int battlesSurvived;
    int enemyUnitsDestroyed;
    int enemyUnitsDestroyedPsychic;
    int enemyUnitsDestroyedRanged;
    int enemyUnitsDestroyedMelee;
    int enemyUnitsDestroyedBattleRound;
    int enemyUnitsDestroyedPsychicBattleRound;
    int enemyUnitsDestroyedRangedBattleRound;
    int enemyUnitsDestroyedMeleeBattleRound;
    int agenda1TallyBattleRound;
    int agenda2TallyBattleRound;
    int agenda3TallyBattleRound;

    // rank
    std::string rank;
    int markedForGreatnessTally;
    std::string battleHonours;
    std::string battleScars;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
            UnitCrusadeData,
            // basic info
            name,
            battleFieldRole,
            crusadeFaction,
            selectableKeywords,
            unitType,
            equipment,
            psychicPowers,
            warlordTraits,
            relics,
            upgrades,
            // experience etc
            powerRating,
            experiencePoints,
            crusadePoints,
            // combat tallies
            battlesPlayed,
            battlesSurvived,
            enemyUnitsDestroyed,
            enemyUnitsDestroyedPsychic,
            enemyUnitsDestroyedRanged,
            enemyUnitsDestroyedMelee,
            // rank
            rank,
            markedForGreatnessTally,
            battleHonours,
            battleScars)
};

#endif // UNITCRUSADEDATA_H
