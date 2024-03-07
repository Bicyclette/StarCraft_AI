#include "BT_ACTION_UPGRADE.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_UPGRADE::BT_ACTION_UPGRADE(std::string name,BT_NODE* parent, BWAPI::UpgradeType type)
    :  BT_ACTION(name,parent) {
    upgradeType = type;
}

BT_NODE::State BT_ACTION_UPGRADE::Evaluate(void* data)
{
    return ReturnState(Upgrade(data));
}

std::string BT_ACTION_UPGRADE::GetDescription()
{
    return "RESEARCH";
}


BT_NODE::State BT_ACTION_UPGRADE::Upgrade(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::UnitType whatUpgrades = upgradeType.whatUpgrades();
    BWAPI::Unit buildingThatUpgrades = NULL;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == whatUpgrades && !unit->isResearching() && unit->isCompleted()) {
            buildingThatUpgrades = unit;
            break;
        }
    }

    if (buildingThatUpgrades) {
        buildingThatUpgrades->upgrade(upgradeType);

        if (upgradeType == BWAPI::UpgradeTypes::Enum::Singularity_Charge) {
            pData->singularityChargeStarted = true;
        }

        const BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None)
            return BT_NODE::FAILURE;
        else return BT_NODE::SUCCESS;
    }

    std::cout << "cpt upgrade";
    return BT_NODE::FAILURE;
}