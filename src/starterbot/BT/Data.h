#pragma once
#include <unordered_set>
#include <BWAPI.h>

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

	int wantedWorkersTotal = 30;

	bool buildProbes = true;
	bool buildArmy = false;
	bool autoBuildPylon = false;
	bool autoBuildGate = false;

	bool pylonIsUnderBuild = false;
	bool gateIsUnderBuild = false;

	bool singularityChargeStarted = false;

	int buildOrderStep = 0;
	static const int buildOrderMaxLength = 20;
	static std::pair<int, BWAPI::UnitType> buildOrder[buildOrderMaxLength];
	static std::function<void(Data* pData)> buildOrderExtension[buildOrderMaxLength];

	void show_info();
};