#include "CONDITIONS_CBK.h"

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
	const int unusedSupply = pData->totalSupply - pData->currSupply;

	const bool canBuild = pData->currMinerals >= 100;
	const bool wantToBuild = pData->autoBuildPylon && !pData->pylonIsUnderBuild && unusedSupply <= pData->thresholdSupply && pData->totalSupply < 400;

	return canBuild && wantToBuild;

}


bool buildGateCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const bool wantToBuild = pData->autoBuildGate && pData->currMinerals >= 250 && !pData->gateIsUnderBuild && pData->currGates < 6;

	return  wantToBuild;
}

bool upgradeSingularityChargeCondition(void* data) {
	Data* pData = static_cast<Data*>(data);

	Tools::UpdateDataValues(pData);

	const bool canUpgrade = pData->currGas >= 150 && pData->currMinerals >= 150 && Tools::IsBuildingAvailable(BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core)
		&& !pData->singularityChargeStarted;
	// Would be better to check via bwapi if the research is done, but don't know how to

	return canUpgrade;
}
