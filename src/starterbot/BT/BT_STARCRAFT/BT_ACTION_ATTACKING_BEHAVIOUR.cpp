#include "BT_ACTION_ATTACKING_BEHAVIOUR.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_ATTACKING_BEHAVIOUR::BT_ACTION_ATTACKING_BEHAVIOUR(std::string name,BT_NODE* parent)
	:  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_ATTACKING_BEHAVIOUR::Evaluate(void* data)
{
	return ReturnState(AttackTroops(data));
}

std::string BT_ACTION_ATTACKING_BEHAVIOUR::GetDescription()
{
	return "Control the attack pattern of troops in the armyAttacking UnitSet";
}

BT_NODE::State BT_ACTION_ATTACKING_BEHAVIOUR::AttackTroops(void* data)
{
	Data* pData = (Data*)data;


	// then compute the power of our army and the power of the enemy army
	// and attack the enemy army if we are stronger
	// if we are weaker, send the army back to the rallyPoint
	double ourPower = 0;
	double enemyPower = 0;

	BWAPI::Position centerArmy = BWAPI::Position(0, 0);
	int nbDragoons = 0;

	for (auto& unit : pData->armyAttacking)
	{
		// Power = (HP + Shields) * Damage
		ourPower += (unit->getHitPoints() + unit->getShields())*unit->getType().groundWeapon().damageAmount();
		if (unit->getType() == BWAPI::UnitTypes::Protoss_Dragoon)
		{
			centerArmy += unit->getPosition();
			nbDragoons++;
		}
	}

	if (!pData->armyAttacking.empty())
	{
		centerArmy /= nbDragoons;
	}

	// get visible ennemy units in radius around army

	const BWAPI::Unitset& enemyUnits = BWAPI::Broodwar->getUnitsInRadius(centerArmy, pData->armyAttentionRadius, BWAPI::Filter::IsEnemy);

	// no enemy units, attack the enemy base

	if (enemyUnits.empty()) {
		// focus on the enemy base then
		for (auto& unit : pData->armyAttacking)
		{
			unit->attack(pData->enemyPosition);
		}
		return BT_NODE::SUCCESS;
	}

	for (auto& unit : enemyUnits)
	{
		// Power = (HP + Shields) * Damage
		enemyPower += (unit->getHitPoints() + unit->getShields())*unit->getType().groundWeapon().damageAmount();
	}

	// FLEE
	if (ourPower < enemyPower) {
		// send the army back to the rallyPoint
		for (auto& unit : pData->armyAttacking)
		{
			unit->move(pData->rallyPosition);
			pData->armyAtRally.insert(unit);
		}
		// pop the armyAttacking UnitSet to the armyAtRally UnitSet
		pData->armyAttacking.clear();
		// store previous enemy power to decide when to attack again
		pData->enemyPower = enemyPower;
		pData->attacking = false;
		return BT_NODE::SUCCESS;
	}

	// now compute the priority of each enemy unit : 
	// Kill units that can attack us first (and add priority to low hp units IN RANGE OF ATTACK
	// then kill units that can't attack us (workers)
	// then kill buildings

	for (auto& myUnit : pData->armyAttacking)
	{
		BWAPI::Unit target = nullptr;
		double targetPriority = 0;
		for (auto& enemyUnit : enemyUnits)
		{
			double priority = 0;
			if (enemyUnit->getType().groundWeapon().maxRange() >= myUnit->getType().groundWeapon().maxRange())
			{
				priority += 100;
			}
			if (enemyUnit->getType().isWorker())
			{
				priority += 50;
			}
			if (enemyUnit->getType().isBuilding())
			{
				priority += 25;
			}
			if (enemyUnit->getHitPoints() + enemyUnit->getShields() < 50)
			{
				priority += 10;
			}
			if (priority > targetPriority)
			{
				target = enemyUnit;
				targetPriority = priority;
			}
		}
		if (target != nullptr)
		{
			myUnit->attack(target, true);
		}
		else
		{
			myUnit->attack(pData->enemyPosition);
		}
	}





	return BT_NODE::SUCCESS;
}
