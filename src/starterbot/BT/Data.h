#pragma once
#include <unordered_set>
#include <BWAPI.h>
#define WANTED_WORKERS_TOTAL 30

class Data {
public:
	int currMinerals;
	int currGas;
	int currProbes;
	int currSupply;
	int totalSupply;
	int thresholdSupply;

	int wantedWorkersTotal;

	bool buildProbes;
	bool buildArmy;
	bool autoBuildPylon;
	bool autoBuildGate;

	bool pylonIsUnderBuild;
	bool gateIsUnderBuild;
};
