#pragma once
#include <unordered_set>
#include <BWAPI.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 30
#define NWANTED_WORKERS_FARMING_MINERALS 10

class Data {
public:
	int currMinerals;
	int currProbes;
	int thresholdMinerals;
	int currSupply;
	int totalSupply;
	int thresholdSupply;

	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMinerals;

	bool buildProbes;
	bool buildArmy;
	bool autoBuildPylon;
	bool autoBuildGate;

	bool pylonIsUnderBuild;
	bool gateIsUnderBuild;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingGas;
};
