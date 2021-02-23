#include "unitcrusadecard.h"
#include "ui_unitcrusadecard.h"

UnitCrusadeCard::UnitCrusadeCard(UnitCrusadeData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitCrusadeCard)
{
    ui->setupUi(this);
    ui->comboBoxRank->installEventFilter(this);
    ui->comboBoxRole->installEventFilter(this);

    this->data = data;

    UpdateView();
    ConnectLinks();
}

UnitCrusadeCard::~UnitCrusadeCard()
{
    delete ui;
}

bool UnitCrusadeCard::eventFilter(QObject *targetQObject, QEvent *currentEvent)
{
    if ((targetQObject == ui->comboBoxRank || targetQObject == ui->comboBoxRole) && currentEvent->type() == QEvent::Wheel)
    {
            return true;
    }
    return QObject::eventFilter(targetQObject, currentEvent);
}

void UnitCrusadeCard::OnUnitSelection(UnitCrusadeData *unit)
{
    data = unit;
    UpdateView();
}

void UnitCrusadeCard::OnNameChanged(const QString value)
{
    auto newValue = value.toStdString();
    if (data->name != newValue){
        data->name = newValue;
        data->SetUnsaved();
        OnDisplayValueChanged();
    }
}

void UnitCrusadeCard::OnBattleFieldRoleChanged(const QString value)
{
    auto newValue = value.toStdString();
    if (data->battleFieldRole != newValue){
        data->battleFieldRole = newValue;
        data->SetUnsaved();
        OnDisplayValueChanged();
    }
}

void UnitCrusadeCard::OnCrusadeFactionChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->crusadeFaction != newValue){
        data->crusadeFaction = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnSelectableKeywordsChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->selectableKeywords != newValue){
        data->selectableKeywords = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnUnitTypeChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->unitType != newValue){
        data->unitType = newValue;
        data->SetUnsaved();
        OnDisplayValueChanged();
    }
}

void UnitCrusadeCard::OnEquipmentChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->equipment != newValue){
        data->equipment = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnPsychicPowersChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->psychicPowers != newValue){
        data->psychicPowers = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnWarlordTraitsChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->warlordTraits != newValue){
        data->warlordTraits = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnRelicsChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->relics != newValue){
        data->relics = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnPowerRatingChanged(int value)
{
    if (data->powerRating != value){
        data->powerRating = value;
        data->SetUnsaved();
        OnDisplayValueChanged();
    }
}

void UnitCrusadeCard::OnExperiencePointsChanged(int value)
{
    if (data->experiencePoints != value){
        data->experiencePoints = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnCrusadePointsChanged(int value)
{
    if(data->crusadePoints != value){
        data->crusadePoints = value;
        data->SetUnsaved();
        OnDisplayValueChanged();
    }
}

void UnitCrusadeCard::OnUpgradesChanged()
{
    auto newValue = ui->plainTextEditUpgrades->toPlainText().toStdString();
    if (data->upgrades != newValue){
        data->upgrades = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnBattlesPlayedChanged(int value)
{
    if (data->battlesPlayed != value){
        data->battlesPlayed = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnBattlesSurvivedChanged(int value)
{
    if (data->battlesSurvived != value){
        data->battlesSurvived = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicBattleroundChanged(int value)
{
    if (data->enemyUnitsDestroyedPsychicBattleRound != value){
        data->enemyUnitsDestroyedPsychicBattleRound = value;
        data->SetUnsaved();
        UpdateEnemyUnitsDestroyedBattleRoundTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedRangedBattleroundChanged(int value)
{
    if (data->enemyUnitsDestroyedRangedBattleRound != value){
        data->enemyUnitsDestroyedRangedBattleRound = value;
        data->SetUnsaved();
        UpdateEnemyUnitsDestroyedBattleRoundTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeBattleroundChanged(int value)
{
    if (data->enemyUnitsDestroyedMeleeBattleRound != value){
        data->enemyUnitsDestroyedMeleeBattleRound = value;
        data->SetUnsaved();
        UpdateEnemyUnitsDestroyedBattleRoundTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicChanged(int value)
{
    if (data->enemyUnitsDestroyedPsychic != value){
        data->enemyUnitsDestroyedPsychic = value;
        data->SetUnsaved();
        UpdateEnemyUnitsDestroyedTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedRangedChanged(int value)
{
    if (data->enemyUnitsDestroyedRanged != value){
        data->enemyUnitsDestroyedRanged = value;
        data->SetUnsaved();
        UpdateEnemyUnitsDestroyedTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeChanged(int value)
{
    if (data->enemyUnitsDestroyedMelee != value){
        data->enemyUnitsDestroyedMelee = value;
        data->SetUnsaved();
        UpdateEnemyUnitsDestroyedTotal();
    }
}

void UnitCrusadeCard::OnAgenda1TallyChanged(int value)
{
    if (data->agenda1TallyBattleRound != value){
        data->agenda1TallyBattleRound = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnAgenda2TallyChanged(int value)
{
    if (data->agenda2TallyBattleRound != value){
        data->agenda2TallyBattleRound = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnAgenda3TallyChanged(int value)
{
    if (data->agenda3TallyBattleRound != value){
        data->agenda3TallyBattleRound = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnRankChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->rank != newValue){
        data->rank = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnMarkedForGreatnessTallyChanged(int value)
{
    if (data->markedForGreatnessTally != value){
        data->markedForGreatnessTally = value;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnBattleHonoursChanged()
{
    auto newValue = ui->plainTextEditBattleHonours->toPlainText().toStdString();
    if (data->battleHonours != newValue) {
        data->battleHonours = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::OnBattleScarsChanged()
{
    auto newValue = ui->plainTextEditBattleScars->toPlainText().toStdString();
    if (data->battleScars != newValue) {
        data->battleScars = newValue;
        data->SetUnsaved();
    }
}

void UnitCrusadeCard::UpdateView()
{
    ui->lineEditName->setText(QString::fromStdString(data->name));
    ui->comboBoxRole->setCurrentText(QString::fromStdString(data->battleFieldRole));
    ui->lineEditCrusadeFaction->setText(QString::fromStdString(data->crusadeFaction));
    ui->lineEditSelectableKeywords->setText(QString::fromStdString(data->selectableKeywords));
    ui->lineEditUnitType->setText(QString::fromStdString(data->unitType));
    ui->lineEditEquipment->setText(QString::fromStdString(data->equipment));
    ui->lineEditPsychicPowers->setText(QString::fromStdString(data->psychicPowers));
    ui->lineEditWarlordTraits->setText(QString::fromStdString(data->warlordTraits));
    ui->lineEditRelics->setText(QString::fromStdString(data->relics));

    ui->lineEditPowerRatingAmount->setText(QString::number(data->powerRating));
    ui->lineEditExperienceAmount->setText(QString::number(data->experiencePoints));
    ui->lineEditCrusadePointsAmount->setText(QString::number(data->crusadePoints));
    ui->plainTextEditUpgrades->setPlainText(QString::fromStdString(data->upgrades));

    ui->lineEditBattlesPlayedAmount->setText(QString::number(data->battlesPlayed));
    ui->lineEditBattlesSurvivedAmount->setText(QString::number(data->battlesSurvived));
    UpdateEnemyUnitsDestroyedBattleRoundTotal();
    ui->lineEditEnemiesDestroyedPsychicBattleRoundAmount->setText(QString::number(data->enemyUnitsDestroyedPsychicBattleRound));
    ui->lineEditEnemiesDestroyedRangedBattleRoundAmount->setText(QString::number(data->enemyUnitsDestroyedRangedBattleRound));
    ui->lineEditEnemiesDestroyedMeleeBattleRoundAmount->setText(QString::number(data->enemyUnitsDestroyedMeleeBattleRound));
    UpdateEnemyUnitsDestroyedTotal();
    ui->lineEditEnemiesDestroyedPsychicTotalAmount->setText(QString::number(data->enemyUnitsDestroyedPsychic));
    ui->lineEditEnemiesDestroyedRangedTotalAmount->setText(QString::number(data->enemyUnitsDestroyedRanged));
    ui->lineEditEnemiesDestroyedMeleeTotalAmount->setText(QString::number(data->enemyUnitsDestroyedMelee));
    ui->lineEditAgenda1TallyAmount->setText(QString::number(data->agenda1TallyBattleRound));
    ui->lineEditAgenda2TallyAmount->setText(QString::number(data->agenda2TallyBattleRound));
    ui->lineEditAgenda3TallyAmount->setText(QString::number(data->agenda3TallyBattleRound));

    ui->comboBoxRank->setCurrentText(QString::fromStdString(data->rank));
    ui->lineEditMarkedForGreatnessTallyAmount->setText(QString::number(data->markedForGreatnessTally));
    ui->plainTextEditBattleHonours->setPlainText(QString::fromStdString(data->battleHonours));
    ui->plainTextEditBattleScars->setPlainText(QString::fromStdString(data->battleScars));

}

void UnitCrusadeCard::UpdateEnemyUnitsDestroyedBattleRoundTotal()
{
    ui->labelEnemiesDestroyedBattleRoundAmount->setText(QString::number(data->GetEnemyUnitsDestroyedBattleRoundTotal()));
}

void UnitCrusadeCard::UpdateEnemyUnitsDestroyedTotal()
{
    ui->labelEnemiesDestroyedTotalAmount->setText(QString::number(data->GetEnemyUnitsDestroyedTotal()));
}

void UnitCrusadeCard::ConnectLinks()
{
    // info
    connect(ui->lineEditName, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnNameChanged);
    connect(ui->comboBoxRole, &QComboBox::currentTextChanged, this, &UnitCrusadeCard::OnBattleFieldRoleChanged);
    connect(ui->lineEditCrusadeFaction, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnCrusadeFactionChanged);
    connect(ui->lineEditSelectableKeywords, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnSelectableKeywordsChanged);
    connect(ui->lineEditUnitType, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnUnitTypeChanged);
    connect(ui->lineEditEquipment, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnEquipmentChanged);
    connect(ui->lineEditPsychicPowers, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnPsychicPowersChanged);
    connect(ui->lineEditWarlordTraits, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnWarlordTraitsChanged);
    connect(ui->lineEditRelics, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnRelicsChanged);

    // points
    connect(ui->lineEditPowerRatingAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnPowerRatingChanged);
    connect(ui->lineEditExperienceAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnExperiencePointsChanged);
    connect(ui->lineEditCrusadePointsAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnCrusadePointsChanged);
    connect(ui->plainTextEditUpgrades, &QPlainTextEdit::textChanged, this, &UnitCrusadeCard::OnUpgradesChanged);

    // combat tallies
    connect(ui->lineEditBattlesPlayedAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnBattlesPlayedChanged);
    connect(ui->lineEditBattlesSurvivedAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnBattlesSurvivedChanged);

    connect(ui->lineEditEnemiesDestroyedPsychicBattleRoundAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicBattleroundChanged);
    connect(ui->lineEditEnemiesDestroyedRangedBattleRoundAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedRangedBattleroundChanged);
    connect(ui->lineEditEnemiesDestroyedMeleeBattleRoundAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeBattleroundChanged);
    connect(ui->lineEditEnemiesDestroyedPsychicTotalAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicChanged);
    connect(ui->lineEditEnemiesDestroyedRangedTotalAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedRangedChanged);
    connect(ui->lineEditEnemiesDestroyedMeleeTotalAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeChanged);

    connect(ui->lineEditAgenda1TallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnAgenda1TallyChanged);
    connect(ui->lineEditAgenda2TallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnAgenda2TallyChanged);
    connect(ui->lineEditAgenda3TallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnAgenda3TallyChanged);

    // rank
    connect(ui->comboBoxRank, &QComboBox::currentTextChanged, this, &UnitCrusadeCard::OnRankChanged);
    connect(ui->lineEditMarkedForGreatnessTallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnMarkedForGreatnessTallyChanged);
    connect(ui->plainTextEditBattleHonours, &QPlainTextEdit::textChanged, this, &UnitCrusadeCard::OnBattleHonoursChanged);
    connect(ui->plainTextEditBattleScars, &QPlainTextEdit::textChanged, this, &UnitCrusadeCard::OnBattleScarsChanged);
}
