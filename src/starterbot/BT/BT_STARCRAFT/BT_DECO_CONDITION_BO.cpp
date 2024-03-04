#include "BT_DECO_CONDITION_BO.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_BO::BT_DECO_CONDITION_BO(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, doProgressBO) {}


std::string BT_DECO_CONDITION_BO::GetDescription()
{
    return "DECO_CONDITION_BO";
}

bool BT_DECO_CONDITION_BO::doProgressBO(void* data)
{
    Data* pData = (Data*)data;

    Tools::UpdateDataValues(pData);

    std::pair<int, BWAPI::UnitType> boStep = pData->buildOrder[pData->buildOrderStep];

    bool reachedProgressPoint = boStep.first * 2 <= pData->currSupply;
    
    BWAPI::UnitType type = boStep.second;

    if (type) return reachedProgressPoint && pData->currMinerals >= type.mineralPrice() && pData->currGas >= type.gasPrice();
   
    else return reachedProgressPoint;

}
