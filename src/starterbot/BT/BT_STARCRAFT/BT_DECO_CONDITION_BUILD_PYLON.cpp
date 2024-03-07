#include "BT_DECO_CONDITION_BUILD_PYLON.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BUILD_PYLON::BT_DECO_CONDITION_BUILD_PYLON(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, doBuildPylon) {}


std::string BT_DECO_CONDITION_BUILD_PYLON::GetDescription()
{
    return "DECO_CONDITION_BUILD_PYLON";
}

bool BT_DECO_CONDITION_BUILD_PYLON::doBuildPylon(void* data)
{
    Data* pData = (Data*)data;

    Tools::UpdateDataValues(pData);

    // Get the amount of supply supply we currently have unused
    const int unusedSupply = pData->totalSupply - pData->currSupply;

    const bool canBuild = pData->currMinerals >= 100;
    const bool wantToBuild = pData->autoBuildPylon && !pData->pylonIsUnderBuild && unusedSupply <= pData->thresholdSupply && pData->totalSupply < 400;

    return canBuild && wantToBuild;

}
