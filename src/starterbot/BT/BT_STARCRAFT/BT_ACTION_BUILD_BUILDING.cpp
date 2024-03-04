#include "BT_ACTION_BUILD_BUILDING.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_BUILD_BUILDING::BT_ACTION_BUILD_BUILDING(std::string name,BT_NODE* parent, BWAPI::UnitType type)
    :  BT_ACTION(name,parent) {
    typeToBuild = type;
}

BT_NODE::State BT_ACTION_BUILD_BUILDING::Evaluate(void* data)
{
    return ReturnState(BuildBuilding(data));
}

std::string BT_ACTION_BUILD_BUILDING::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_BUILDING::BuildBuilding(void* data)
{
    Data* pData = (Data*)data;


    const bool startedBuilding = Tools::BuildBuilding(typeToBuild);

    if (startedBuilding)
    {
        if (typeToBuild == BWAPI::UnitTypes::Enum::Protoss_Pylon)
        {
            pData->pylonIsUnderBuild = true;
        }
        if (typeToBuild == BWAPI::UnitTypes::Enum::Protoss_Gateway) {
            pData->gateIsUnderBuild = true;
        }
    }

    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}