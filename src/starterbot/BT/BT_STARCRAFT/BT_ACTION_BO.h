#pragma once
#include <cassert>
#include "BT_ACTION.h"

//Evaluates the specified conditional task. If the conditional task returns success then the child task is run and the child status is returned. If the conditional task does not
// return success then the child task is not run and a failure status is immediately returned.
// 
//--------------------
class BT_ACTION_BO : public BT_ACTION {
public:
    BT_ACTION_BO(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State ProgressBO(void* data);
};
//----------