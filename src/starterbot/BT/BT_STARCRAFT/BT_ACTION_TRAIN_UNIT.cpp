#include "BT_ACTION_TRAIN_UNIT.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_TRAIN_UNIT::BT_ACTION_TRAIN_UNIT(std::string name,BT_NODE* parent, BWAPI::UnitType type)
    :  BT_ACTION(name,parent) {
    typeToBuild = type;
}

BT_NODE::State BT_ACTION_TRAIN_UNIT::Evaluate(void* data)
{
    return ReturnState(TrainUnit(data));
}

std::string BT_ACTION_TRAIN_UNIT::GetDescription()
{
    return "TRAIN UNIT";
}


BT_NODE::State BT_ACTION_TRAIN_UNIT::TrainUnit(void* data)
{
    const Data* pData = (Data*)data;

    const BWAPI::UnitType whatBuilds = typeToBuild.whatBuilds().first;
    BWAPI::Unit buildingThatBuilds = NULL;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == whatBuilds && !unit->isTraining() && unit->isCompleted()) {
            buildingThatBuilds = unit;
            break;
        }
    }

    if (buildingThatBuilds) {
        buildingThatBuilds->train(typeToBuild);
        const BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None)
            return BT_NODE::FAILURE;
        else return BT_NODE::SUCCESS;
    }

    std::cout << "cpt unit";
    return BT_NODE::FAILURE;
}