#include "BT_ACTION_SEND_TROOPS.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_SEND_TROOPS::BT_ACTION_SEND_TROOPS(std::string name,BT_NODE* parent)
	:  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_SEND_TROOPS::Evaluate(void* data)
{
	return ReturnState(SendTroops(data));
}

std::string BT_ACTION_SEND_TROOPS::GetDescription()
{
	return "SEND TROOPS TO RALLYPOINT";
}

BT_NODE::State BT_ACTION_SEND_TROOPS::SendTroops(void* data)
{
	Data* pData = (Data*)data;

	// if we have enough units at base, send them to the rally point
	int totalAttackUnitsAtBase = pData->armyAtBase.size();
	for (auto& unit : pData->armyAtBase)
	{
		unit->attack(pData->rallyPosition);
		pData->armyAtRally.insert(unit);
	}
	pData->armyAtBase.clear();
	// force units supposed to be in rally but no in the rally position to go to the rally
	for (auto& unit : pData->armyAtRally)
	{
		if (unit->getDistance(pData->rallyPosition) > pData->armyAtRallyRadius)
		{
			unit->attack(pData->rallyPosition);
		}
	}

	std::cout << "Sending " << totalAttackUnitsAtBase <<" troops to rally point"<< std::endl;
	return BT_NODE::SUCCESS;
}