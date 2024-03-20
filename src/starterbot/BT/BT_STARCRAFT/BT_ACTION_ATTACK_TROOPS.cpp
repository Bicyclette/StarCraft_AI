#include "BT_ACTION_ATTACK_TROOPS.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_ATTACK_TROOPS::BT_ACTION_ATTACK_TROOPS(std::string name,BT_NODE* parent)
	:  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_ATTACK_TROOPS::Evaluate(void* data)
{
	return ReturnState(AttackTroops(data));
}

std::string BT_ACTION_ATTACK_TROOPS::GetDescription()
{
	return "SEND TROOPS TO ATTACK ENEMY BASE";
}

BT_NODE::State BT_ACTION_ATTACK_TROOPS::AttackTroops(void* data)
{
	Data* pData = (Data*)data;

	for (auto& unit : pData->armyAttacking)
	{
		unit->attack(pData->enemyPosition);
	}

	std::cout<<"Attacking enemy base"<<std::endl;
	return BT_NODE::SUCCESS;


}

