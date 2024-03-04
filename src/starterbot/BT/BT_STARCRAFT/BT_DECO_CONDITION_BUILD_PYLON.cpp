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

    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

    return pData->autoBuildPylon && !pData->pylonIsUnderBuild && unusedSupply <= pData->thresholdSupply && pData->currMinerals >= 100 && pData->totalSupply < 200;

}
