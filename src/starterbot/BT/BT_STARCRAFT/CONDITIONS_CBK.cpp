#include "CONDITIONS_CBK.h"

bool sendWorkersToGasCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const bool canDo = Tools::UnitExists(BWAPI::UnitTypes::Enum::Protoss_Assimilator) && pData->currProbes > 0;
	const bool wantToDo = pData->probesOnGas < pData->wantedProbesOnGas && !pData->justSentToGas;
	if (pData->justSentToGas) pData->justSentToGas = false;

	return canDo && wantToDo;
}

bool buildProbeCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	// Get the amount of supply supply we currently have unused
	const int unusedSupply = pData->totalSupply - pData->currSupply;

	const bool canBuild = Tools::IsBuildingAvailable(BWAPI::UnitTypes::Enum::Protoss_Nexus) && unusedSupply >= 2 && pData->currMinerals >= 50;
	const bool wantToBuild = pData->buildProbes && pData->currProbes < pData->wantedWorkersTotal;

	return  canBuild && wantToBuild;
}

bool buildDragoonCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	// Get the amount of supply supply we currently have unused
	const int unusedSupply = pData->totalSupply - pData->currSupply;
	const bool canBuild = Tools::IsBuildingAvailable(BWAPI::UnitTypes::Enum::Protoss_Gateway) && unusedSupply >= 4
		&& pData->currMinerals >= 125 && pData->currGas >= 50 && Tools::UnitExists(BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core);
	const bool wantToBuild = pData->buildArmy;

	return  canBuild && wantToBuild;
}


bool buildZealotCondition(void* data){
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	// Get the amount of supply supply we currently have unused
	const int unusedSupply = pData->totalSupply - pData->currSupply;
	const bool canBuild = Tools::IsBuildingAvailable(BWAPI::UnitTypes::Enum::Protoss_Gateway) && unusedSupply >= 4
		&& pData->currMinerals >= 100;
	const bool wantToBuild = pData->buildArmy && (pData->currGas < 50 || !Tools::UnitExists(BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core));

	return  canBuild && wantToBuild;
}

bool buildPylonCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	// Get the amount of supply supply we currently have unused
	const int unusedSupply = Tools::GetTotalSupply(true) - pData->currSupply;

	const bool canBuild = pData->currMinerals >= 100;
	const bool wantToBuild = pData->autoBuildPylon && unusedSupply <= pData->thresholdSupply && pData->totalSupply < 400;

	return canBuild && wantToBuild;
}


bool buildGateCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const bool wantToBuild = pData->autoBuildGate && pData->currMinerals >= 250 && !pData->gateIsUnderBuild && pData->currGates < 6;

	return  wantToBuild;
}

bool buildAssimilatorCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const bool wantToBuild = pData->autoBuildAssimilator && !Tools::BuildingExistsOrOrderToBuildGiven(BWAPI::UnitTypes::Enum::Protoss_Assimilator);
	const bool canBuild = pData->currMinerals >= 100;

	return  wantToBuild && canBuild;
}

bool upgradeSingularityChargeCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const bool canUpgrade = pData->currGas >= 150 && pData->currMinerals >= 150 && Tools::IsBuildingAvailable(BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core)
		&& !pData->singularityChargeStarted;
	// Would be better to check via bwapi if the research is done, but don't know how to

	return canUpgrade;
}

bool mineralsHigherThan100(void* data) {

	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);
	return pData->currMinerals > 100;
}

bool pylonUnderBuild(void* data) {
	for (auto& unit : BWAPI::Broodwar->self()->getUnits())
	{
		if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Pylon && !unit->isCompleted())
		{
			return true;
		}
	}
	return false;
}

bool sendTroopsCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const int totalAttackUnitsAtBase = pData->armyAtBase.size();
	//int totalAttackUnitsAtRally = pData->armyAtRally.size();
	const bool wantToDo = totalAttackUnitsAtBase > 4;
	const bool canDo = !pData->sendingToRally;

	// The multiple time behaviour is handled in the update function for data
	// it resets the "sendingToRally" bool to false when enough units (more than the current
	// value defined in this function) are at the base
	// This is done to avoid sending the order to base units to go to rally
	// at every frame when the condition is met


	return canDo && wantToDo;
}

bool attackTroopsCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);
	const int totalAttackUnitsAtRally = pData->armyAtRally.size();
	const bool wantToDo = totalAttackUnitsAtRally > 4;

	const bool canDo = !pData->attacking;

	// Create a squad of units that will attack the base
	if (canDo && wantToDo) {
		pData->attacking = true;
		for (auto& unit : pData->armyAtRally)
		{
			pData->armyAttacking.insert(unit);
		}
	}
	
	return canDo && wantToDo;

}

bool attackingBehaviourCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	BWAPI::Unitset realArmy = BWAPI::Unitset();

	for (auto& unit : pData->armyAttacking)
	{
		if (unit->exists())
		{
			realArmy.insert(unit);
		}
	}

	pData->armyAttacking = realArmy;
	bool canDo = realArmy.size() > 0;

	// rush B
	bool wantToDo = true;

	return canDo && wantToDo;
}
