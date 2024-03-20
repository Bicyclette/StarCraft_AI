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

	std::cout<<"Army at base :"<<pData->armyAtBase.size()<<std::endl;

	// if we have enough units at base, send them to the rally point
	for (auto& unit : pData->armyAtBase)
	{
		unit->move(pData->rallyPosition);

	}
	std::cout << "Sending troops to rally point"<< std::endl;
	pData->sendingToRally = true;
	return BT_NODE::SUCCESS;
}