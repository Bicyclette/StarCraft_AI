#include "Data.h"

std::pair<int, BWAPI::UnitType> Data::buildOrder[Data::buildOrderMaxLength];
std::function<void(Data*)> Data::buildOrderExtension[Data::buildOrderMaxLength];

BWAPI::TilePosition Data::pylonPosList[Data::prepositionnedBuildingMaxAmount];
BWAPI::TilePosition Data::gatePosList[Data::prepositionnedBuildingMaxAmount];
BWAPI::TilePosition Data::cyberPosList[Data::prepositionnedBuildingMaxAmount];
int Data::pylonPosStep = 0;
int Data::gatePosStep = 0;
int Data::cyberPosStep = 0;


void Data::show_info() {
    std::cout << "pData info :" << std::endl;
    std::cout << "currMinerals: " << currMinerals << std::endl;
    std::cout << "currGas: " << currGas << std::endl;
    std::cout << "currProbes: " << currProbes << std::endl;
    std::cout << "currSupply: " << currSupply << std::endl;
    std::cout << "totalSupply: " << totalSupply << std::endl;
    std::cout << "thresholdSupply: " << thresholdSupply << std::endl;
    std::cout << "wantedWorkersTotal: " << wantedWorkersTotal << std::endl;
    std::cout << "buildProbes: " << buildProbes << std::endl;
    std::cout << "buildArmy: " << buildArmy << std::endl;
    std::cout << "autoBuildPylon: " << autoBuildPylon << std::endl;
    std::cout << "autoBuildGate: " << autoBuildGate << std::endl;
    std::cout << "pylonIsUnderBuild: " << pylonIsUnderBuild << std::endl;
    std::cout << "gateIsUnderBuild: " << gateIsUnderBuild << std::endl;
    std::cout << "buildOrderStep: " << buildOrderStep << std::endl;
    std::cout << std::endl;
}