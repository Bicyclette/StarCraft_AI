#include "BT_DECO_CONDITION_BUILD_PROBE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_PROBE::BT_DECO_CONDITION_BUILD_PROBE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, doBuildProbe) {}


std::string BT_DECO_CONDITION_BUILD_PROBE::GetDescription()
{
    return "DECO_CONDITION_BUILD_PROBE";
}

bool BT_DECO_CONDITION_BUILD_PROBE::doBuildProbe(void* data)
{
    Data* pData = (Data*)data;

    Tools::UpdateDataValues(pData);

    // Get the amount of supply supply we currently have unused
    const int unusedSupply = pData->totalSupply - pData->currSupply;

    const bool canBuild = Tools::IsBuildingAvailable(BWAPI::UnitTypes::Enum::Protoss_Nexus) && unusedSupply >=2 && pData->currMinerals >= 50;
    const bool wantToBuild = pData->buildProbes && pData->currProbes < pData->wantedWorkersTotal;
    
    return  canBuild && wantToBuild;

}
