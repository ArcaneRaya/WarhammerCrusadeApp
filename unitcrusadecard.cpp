#include "unitcrusadecard.h"
#include "ui_unitcrusadecard.h"

UnitCrusadeCard::UnitCrusadeCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitCrusadeCard)
{
    ui->setupUi(this);
    ui->comboBoxRank->installEventFilter(this);
    ui->comboBoxRole->installEventFilter(this);

    ui->comboBoxRole->clear();

    this->data = nullptr;

    UpdateView();
}

UnitCrusadeCard::~UnitCrusadeCard()
{
    delete ui;
}

void UnitCrusadeCard::SetBattlefieldRoleOptions(const QStringList * options)
{
    ui->comboBoxRole->clear();
    ui->comboBoxRole->insertItems(0 ,*options);
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
    if (data != nullptr){
        if (isConnected == false) {
            ConnectLinks();
        }
    } else {
        if (isConnected) {
            DisconnectLinks();
        }
    }
    UpdateView();
}

void UnitCrusadeCard::OnNameChanged(const QString value)
{
    auto newValue = value.toStdString();
    if (data->name != newValue){
        data->name = newValue;
        DataModified();
        DisplayValueChanged();
    }
}

void UnitCrusadeCard::OnBattleFieldRoleChanged(const QString value)
{
    auto newValue = value.toStdString();
    if (data->battleFieldRole != newValue){
        data->battleFieldRole = newValue;
        DataModified();
        DisplayValueChanged();
    }
}

void UnitCrusadeCard::OnCrusadeFactionChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->crusadeFaction != newValue){
        data->crusadeFaction = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnSelectableKeywordsChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->selectableKeywords != newValue){
        data->selectableKeywords = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnUnitTypeChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->unitType != newValue){
        data->unitType = newValue;
        DataModified();
        DisplayValueChanged();
    }
}

void UnitCrusadeCard::OnEquipmentChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->equipment != newValue){
        data->equipment = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnPsychicPowersChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->psychicPowers != newValue){
        data->psychicPowers = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnWarlordTraitsChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->warlordTraits != newValue){
        data->warlordTraits = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnRelicsChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->relics != newValue){
        data->relics = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnPowerRatingChanged(int value)
{
    if (data->powerRating != value){
        data->powerRating = value;
        DataModified();
        DisplayValueChanged();
    }
}

void UnitCrusadeCard::OnExperiencePointsChanged(int value)
{
    if (data->experiencePoints != value){
        data->experiencePoints = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnCrusadePointsChanged(int value)
{
    if(data->crusadePoints != value){
        data->crusadePoints = value;
        DataModified();
        DisplayValueChanged();
    }
}

void UnitCrusadeCard::OnUpgradesChanged()
{
    auto newValue = ui->plainTextEditUpgrades->toPlainText().toStdString();
    if (data->upgrades != newValue){
        data->upgrades = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnBattlesPlayedChanged(int value)
{
    if (data->battlesPlayed != value){
        data->battlesPlayed = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnBattlesSurvivedChanged(int value)
{
    if (data->battlesSurvived != value){
        data->battlesSurvived = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicBattleroundChanged(int value)
{
    if (data->enemyUnitsDestroyedPsychicBattleRound != value){
        data->enemyUnitsDestroyedPsychicBattleRound = value;
        DataModified();
        UpdateEnemyUnitsDestroyedBattleRoundTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedRangedBattleroundChanged(int value)
{
    if (data->enemyUnitsDestroyedRangedBattleRound != value){
        data->enemyUnitsDestroyedRangedBattleRound = value;
        DataModified();
        UpdateEnemyUnitsDestroyedBattleRoundTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeBattleroundChanged(int value)
{
    if (data->enemyUnitsDestroyedMeleeBattleRound != value){
        data->enemyUnitsDestroyedMeleeBattleRound = value;
        DataModified();
        UpdateEnemyUnitsDestroyedBattleRoundTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicChanged(int value)
{
    if (data->enemyUnitsDestroyedPsychic != value){
        data->enemyUnitsDestroyedPsychic = value;
        DataModified();
        UpdateEnemyUnitsDestroyedTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedRangedChanged(int value)
{
    if (data->enemyUnitsDestroyedRanged != value){
        data->enemyUnitsDestroyedRanged = value;
        DataModified();
        UpdateEnemyUnitsDestroyedTotal();
    }
}

void UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeChanged(int value)
{
    if (data->enemyUnitsDestroyedMelee != value){
        data->enemyUnitsDestroyedMelee = value;
        DataModified();
        UpdateEnemyUnitsDestroyedTotal();
    }
}

void UnitCrusadeCard::OnAgenda1TallyChanged(int value)
{
    if (data->agenda1TallyBattleRound != value){
        data->agenda1TallyBattleRound = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnAgenda2TallyChanged(int value)
{
    if (data->agenda2TallyBattleRound != value){
        data->agenda2TallyBattleRound = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnAgenda3TallyChanged(int value)
{
    if (data->agenda3TallyBattleRound != value){
        data->agenda3TallyBattleRound = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnRankChanged(const QString value)
{
    auto newValue = value.toStdString();
    if(data->rank != newValue){
        data->rank = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnMarkedForGreatnessTallyChanged(int value)
{
    if (data->markedForGreatnessTally != value){
        data->markedForGreatnessTally = value;
        DataModified();
    }
}

void UnitCrusadeCard::OnBattleHonoursChanged()
{
    auto newValue = ui->plainTextEditBattleHonours->toPlainText().toStdString();
    if (data->battleHonours != newValue) {
        data->battleHonours = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::OnBattleScarsChanged()
{
    auto newValue = ui->plainTextEditBattleScars->toPlainText().toStdString();
    if (data->battleScars != newValue) {
        data->battleScars = newValue;
        DataModified();
    }
}

void UnitCrusadeCard::UpdateView()
{
    if(data == nullptr)
    {
        setVisible(false);
        return;
    }
    setVisible(true);

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
    activeConnections.push_back(connect(ui->lineEditName, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnNameChanged));
    activeConnections.push_back(connect(ui->comboBoxRole, &QComboBox::currentTextChanged, this, &UnitCrusadeCard::OnBattleFieldRoleChanged));
    activeConnections.push_back(connect(ui->lineEditCrusadeFaction, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnCrusadeFactionChanged));
    activeConnections.push_back(connect(ui->lineEditSelectableKeywords, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnSelectableKeywordsChanged));
    activeConnections.push_back(connect(ui->lineEditUnitType, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnUnitTypeChanged));
    activeConnections.push_back(connect(ui->lineEditEquipment, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnEquipmentChanged));
    activeConnections.push_back(connect(ui->lineEditPsychicPowers, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnPsychicPowersChanged));
    activeConnections.push_back(connect(ui->lineEditWarlordTraits, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnWarlordTraitsChanged));
    activeConnections.push_back(connect(ui->lineEditRelics, &QLineEdit::textChanged, this, &UnitCrusadeCard::OnRelicsChanged));

    // points
    activeConnections.push_back(connect(ui->lineEditPowerRatingAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnPowerRatingChanged));
    activeConnections.push_back(connect(ui->lineEditExperienceAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnExperiencePointsChanged));
    activeConnections.push_back(connect(ui->lineEditCrusadePointsAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnCrusadePointsChanged));
    activeConnections.push_back(connect(ui->plainTextEditUpgrades, &QPlainTextEdit::textChanged, this, &UnitCrusadeCard::OnUpgradesChanged));

    // combat tallies
    activeConnections.push_back(connect(ui->lineEditBattlesPlayedAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnBattlesPlayedChanged));
    activeConnections.push_back(connect(ui->lineEditBattlesSurvivedAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnBattlesSurvivedChanged));

    activeConnections.push_back(connect(ui->lineEditEnemiesDestroyedPsychicBattleRoundAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicBattleroundChanged));
    activeConnections.push_back(connect(ui->lineEditEnemiesDestroyedRangedBattleRoundAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedRangedBattleroundChanged));
    activeConnections.push_back(connect(ui->lineEditEnemiesDestroyedMeleeBattleRoundAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeBattleroundChanged));
    activeConnections.push_back(connect(ui->lineEditEnemiesDestroyedPsychicTotalAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedPsychicChanged));
    activeConnections.push_back(connect(ui->lineEditEnemiesDestroyedRangedTotalAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedRangedChanged));
    activeConnections.push_back(connect(ui->lineEditEnemiesDestroyedMeleeTotalAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnEnemyUnitsDestroyedMeleeChanged));

    activeConnections.push_back(connect(ui->lineEditAgenda1TallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnAgenda1TallyChanged));
    activeConnections.push_back(connect(ui->lineEditAgenda2TallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnAgenda2TallyChanged));
    activeConnections.push_back(connect(ui->lineEditAgenda3TallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnAgenda3TallyChanged));

    // rank
    activeConnections.push_back(connect(ui->comboBoxRank, &QComboBox::currentTextChanged, this, &UnitCrusadeCard::OnRankChanged));
    activeConnections.push_back(connect(ui->lineEditMarkedForGreatnessTallyAmount, &IntValueLineEdit::IntValueChanged, this, &UnitCrusadeCard::OnMarkedForGreatnessTallyChanged));
    activeConnections.push_back(connect(ui->plainTextEditBattleHonours, &QPlainTextEdit::textChanged, this, &UnitCrusadeCard::OnBattleHonoursChanged));
    activeConnections.push_back(connect(ui->plainTextEditBattleScars, &QPlainTextEdit::textChanged, this, &UnitCrusadeCard::OnBattleScarsChanged));

    isConnected = true;
}

void UnitCrusadeCard::DisconnectLinks()
{
    for (int i = activeConnections.size() - 1; i >= 0 ;i--)
    {
        disconnect(activeConnections[i]);
    }
    activeConnections.clear();
    isConnected = false;
}
