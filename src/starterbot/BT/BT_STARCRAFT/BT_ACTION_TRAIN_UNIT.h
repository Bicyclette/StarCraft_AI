#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_ACTION_TRAIN_UNIT : public BT_ACTION {
public:
    BT_ACTION_TRAIN_UNIT(std::string name, BT_NODE* parent, BWAPI::UnitType type);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State TrainUnit(void* data);

    BWAPI::UnitType typeToBuild;
};
//----------