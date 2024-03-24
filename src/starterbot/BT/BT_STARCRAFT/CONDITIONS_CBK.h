#pragma once
#include <BT.h>
#include "Data.h"
#include "Tools.h"


bool sendWorkersToGasCondition(void* data);

bool buildProbeCondition(void* data);
bool buildDragoonCondition(void* data);
bool buildZealotCondition(void* data);

bool buildPylonCondition(void* data);
bool buildGateCondition(void* data);
bool buildAssimilatorCondition(void* data);

bool upgradeSingularityChargeCondition(void* data);

bool mineralsHigherThan100(void* data);

bool pylonUnderBuild(void* data);

bool sendTroopsCondition(void* data);
bool attackTroopsCondition(void* data);
bool attackingBehaviourCondition(void* data);

bool unitInEnemyBaseCondition(void* data);
bool enemyBaseEmptyCondition(void* data);
bool seeEnemyCondition(void* data);
