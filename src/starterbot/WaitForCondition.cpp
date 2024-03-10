#include "WaitForCondition.h"

WaitForCondition::WaitForCondition(BT_DECO_CONDITION::CONDITION_CBK argCondition, std::function<void(void*)> argAction) : condition(argCondition), action(argAction) {}

bool WaitForCondition::evaluate(void* data) {
    const bool conditionSatisfied = condition(data);
    if (conditionSatisfied) {
        action(data);
        return true;
    }
    return false;
}