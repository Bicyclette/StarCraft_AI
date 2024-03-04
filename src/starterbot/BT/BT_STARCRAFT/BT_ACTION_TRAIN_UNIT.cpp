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
    return "TRAIN WORKER";
}


BT_NODE::State BT_ACTION_TRAIN_UNIT::TrainUnit(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
    const BWAPI::Unit myDepot = Tools::GetDepot();

    // if we have a valid depot unit and it's currently not training something, train a worker
    // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
    if (myDepot && !myDepot->isTraining()) { 
        myDepot->train(workerType); 
        BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if(error!=BWAPI::Errors::None)
            return BT_NODE::FAILURE;
        else return BT_NODE::SUCCESS;
    }

    if (typeToBuild == BWAPI::UnitTypes::Enum::Protoss_Probe) {
        const BWAPI::Unit myDepot = Tools::GetDepot();
        if (myDepot && !myDepot->isTraining()) {
            myDepot->train(workerType);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}