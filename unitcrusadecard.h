#ifndef UNITCRUSADECARD_H
#define UNITCRUSADECARD_H

#include <QWidget>

#include "unitcrusadedata.h"

namespace Ui {
class UnitCrusadeCard;
}

class UnitCrusadeCard : public QWidget
{
    Q_OBJECT

public:
    explicit UnitCrusadeCard(UnitCrusadeData *data, QWidget *parent = nullptr);
    ~UnitCrusadeCard();

    bool eventFilter(QObject *o, QEvent *ev);

signals:
    void DisplayValueChanged();
    void DataModified();

public slots:
    void OnUnitSelection(UnitCrusadeData *unit);

private slots:
    // info
    void OnNameChanged(QString value);
    void OnBattleFieldRoleChanged(QString value);
    void OnCrusadeFactionChanged(QString value);
    void OnSelectableKeywordsChanged(QString value);
    void OnUnitTypeChanged(QString value);
    void OnEquipmentChanged(QString value);
    void OnPsychicPowersChanged(QString value);
    void OnWarlordTraitsChanged(QString value);
    void OnRelicsChanged(QString value);

    // points
    void OnPowerRatingChanged(int value);
    void OnExperiencePointsChanged(int value);
    void OnCrusadePointsChanged(int value);
    void OnUpgradesChanged();

    // combat tallies
    void OnBattlesPlayedChanged(int value);
    void OnBattlesSurvivedChanged(int value);

    void OnEnemyUnitsDestroyedPsychicBattleroundChanged(int value);
    void OnEnemyUnitsDestroyedRangedBattleroundChanged(int value);
    void OnEnemyUnitsDestroyedMeleeBattleroundChanged(int value);
    void OnEnemyUnitsDestroyedPsychicChanged(int value);
    void OnEnemyUnitsDestroyedRangedChanged(int value);
    void OnEnemyUnitsDestroyedMeleeChanged(int value);

    void OnAgenda1TallyChanged(int value);
    void OnAgenda2TallyChanged(int value);
    void OnAgenda3TallyChanged(int value);

    // rank
    void OnRankChanged(QString value);
    void OnMarkedForGreatnessTallyChanged(int value);
    void OnBattleHonoursChanged();
    void OnBattleScarsChanged();

private:
    void UpdateView();
    void UpdateEnemyUnitsDestroyedBattleRoundTotal();
    void UpdateEnemyUnitsDestroyedTotal();
    void ConnectLinks();
    Ui::UnitCrusadeCard *ui;
    UnitCrusadeData *data;
};

#endif // UNITCRUSADECARD_H
