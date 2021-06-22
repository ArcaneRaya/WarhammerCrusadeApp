#include "generalcrusadedata.h"

GeneralCrusadeData::GeneralCrusadeData()
{

}

void GeneralCrusadeData::GetBattlefieldRolesStringList(QStringList *list)
{
    list->clear();
    for(auto &role : roles){
        QString roleName = QString::fromStdString(role.name);
        list->append(roleName);
    }
}
