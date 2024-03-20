#pragma once
//#define BT_DEBUG_VERBOSE
 
#include "BT_NODE.h"
#include "BT_LEAF.h"
#include "BT_ACTION.h"
#include "BT_DECORATOR.h"

//Composite notes
#include "BT_SEQUENCER.h"
#include "BT_SELECTOR.h"
#include "BT_PARALLEL_SEQUENCER.h"
#include "BT_PARALLEL_SELECTOR.h"

//Decorators
#include "BT_DECO_CONDITION.h"
#include "BT_DECO_COND_GREATER_THAN.h"
#include "BT_DECO_COND_LESSER_THAN.h"

#include "BT_DECO_INVERTER.h"
#include "BT_DECO_REPEATER.h"
#include "BT_DECO_RETURN_FAILURE.h"
#include "BT_DECO_RETURN_SUCCESS.h"
#include "BT_DECO_UNTIL_FAILURE.h"
#include "BT_DECO_UNTIL_SUCCESS.h"

// Conditions
#include "BT_CONDITION.h"
#include "BT_COND_GREATER_THAN.h"
#include "BT_COND_LESSER_THAN.h"

///Decorator Conditions
#include "BT_DECO_CONDITION_BUILD_PYLON.h"
#include "BT_DECO_CONDITION_BO.h"


///Actions
#include "BT_ACTION_IDLE.h"
#include "BT_ACTION_WAIT.h"
#include "BT_ACTION_LOG.h"

#include "BT_ACTION_SEND_TROOPS.h"
#include "BT_ACTION_ATTACK_TROOPS.h"

#include "BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"
#include "BT_ACTION_SEND_WORKERS_TO_GAS.h"
#include "BT_ACTION_TRAIN_UNIT.h"
#include "BT_ACTION_BUILD_BUILDING.h"
#include "BT_ACTION_BO.h"
#include "BT_ACTION_UPGRADE.h"

