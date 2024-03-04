#include "BT_ACTION_BO.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_ACTION_BO::BT_ACTION_BO(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BO::Evaluate(void* data)
{
    return ReturnState(ProgressBO(data));
}

std::string BT_ACTION_BO::GetDescription()
{
    return "Execute build order step and progress";
}
BT_NODE::State BT_ACTION_BO::ProgressBO(void* data)
{
    Data* pData = (Data*)data;

    Tools::UpdateDataValues(pData);

    BWAPI::UnitType type = pData->buildOrder[pData->buildOrderStep].second;

    if (type)
    {
        const bool startedBuilding = Tools::BuildBuilding(type);

        if (startedBuilding)
        {
            if (type == BWAPI::UnitTypes::Enum::Protoss_Pylon)
            {
                pData->pylonIsUnderBuild = true;
            }
            if (type == BWAPI::UnitTypes::Enum::Protoss_Gateway) {
                pData->gateIsUnderBuild = true;
            }
            pData->buildOrderExtension[pData->buildOrderStep]();
            pData->buildOrderStep++;
        }

        return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
    }

    else {
        pData->buildOrderExtension[pData->buildOrderStep]();
        pData->buildOrderStep++;
        return BT_NODE::SUCCESS;
    }


}
