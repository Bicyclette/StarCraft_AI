#pragma once
#include <unordered_set>
#include <BWAPI.h>
#include "WaitForCondition.h"

class Data {
public:
	int currMinerals;
	int currGas;
	int currProbes;
	int currGates;
	int currSupply;
	int totalSupply;
	int thresholdSupply;

	int probesOnGas;
	bool justSentToGas = false; //There is a delay between "probe is asked to mine" "probe->isGatheringGas() =true"

	int wantedWorkersTotal = 30;
	int wantedProbesOnGas = 0;

	bool spawnOnTop;

	// Army Units

	int currZealots;
	int currDragoons;
	int zealotsAtRally;
	int dragoonsAtRally;

	BWAPI::Unitset armyAtBase = BWAPI::Unitset();
	BWAPI::Unitset armyAtRally = BWAPI::Unitset();
	BWAPI::Unitset armyAttacking = BWAPI::Unitset();

	int armyAttentionRadius = 500;
	int armyAtBaseRadius = 950;
	int armyAtRallyRadius = 400;
	int enemyBaseRadius = 200;

	bool defendingBase = true;
	bool attacking = false;
	bool hasBeenInEmenyBase = false;

	double enemyPower = 0;

	// Build

	bool buildProbes = true;
	bool buildArmy = false;
	bool autoBuildPylon = false;
	bool autoBuildGate = false;
	bool autoBuildAssimilator = false;

	bool pylonIsUnderBuild = false;
	bool gateIsUnderBuild = false;

	bool singularityChargeStarted = false;

	int buildOrderStep = 0;
	static const int buildOrderMaxLength = 20;
	static std::pair<int, BWAPI::UnitType> buildOrder[buildOrderMaxLength];
	static std::function<void(Data* pData)> buildOrderExtension[buildOrderMaxLength];

	BWAPI::Position enemyPosition;
	BWAPI::Position basePosition;
	BWAPI::Position rallyPosition;

	std::list<WaitForCondition> waitForConditionList;

	static const int prepositionnedBuildingMaxAmount = 10;

	static BWAPI::TilePosition pylonPosList[prepositionnedBuildingMaxAmount];
	static int pylonPosStep;
	static BWAPI::TilePosition gatePosList[prepositionnedBuildingMaxAmount];
	static int gatePosStep;
	static BWAPI::TilePosition cyberPosList [prepositionnedBuildingMaxAmount];
	static int cyberPosStep;

	BWAPI::Position rallyAtBase;


	void show_info();
};