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

    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    
    return pData->buildProbes && unusedSupply > 0 && pData->currMinerals >= 50 && pData->currProbes < NWANTED_WORKERS_TOTAL;

}
