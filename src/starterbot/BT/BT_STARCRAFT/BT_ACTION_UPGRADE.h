#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_ACTION_UPGRADE : public BT_ACTION {
public:
    BT_ACTION_UPGRADE(std::string name, BT_NODE* parent, BWAPI::UpgradeType type);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State Upgrade(void* data);

    BWAPI::UpgradeType upgradeType;
};
//----------