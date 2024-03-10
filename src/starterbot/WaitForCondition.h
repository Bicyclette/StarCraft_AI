#pragma once

#include "MapTools.h"
#include <BWAPI.h>
#include "BT.h"

class WaitForCondition {
private:
    BT_DECO_CONDITION::CONDITION_CBK condition;
    std::function<void(void* data)> action;

public:
    WaitForCondition(BT_DECO_CONDITION::CONDITION_CBK condition, std::function<void(void*)> action);
    bool evaluate(void* data);
};