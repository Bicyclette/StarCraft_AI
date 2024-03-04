#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_ACTION_BUILD_BUILDING : public BT_ACTION {
public:
    BT_ACTION_BUILD_BUILDING(std::string name, BT_NODE* parent, BWAPI::UnitType type);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State BuildBuilding(void* data);

    BWAPI::UnitType typeToBuild;
};
//----------