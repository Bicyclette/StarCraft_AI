#include "BuildOrder.h"

void setupBaseBuildOrder(Data* pData) {
    for (int i = 0; i < Data::buildOrderMaxLength; ++i) {
        Data::buildOrderExtension[i] = [](Data* pData) {};
    }
}

void setUpOneBaseAllIn(Data* pData) {
    pData->buildOrder[0] = std::make_pair(8, NULL);
    pData->buildOrderExtension[0] = [](Data* pData) {std::cout << "BO-0\n";pData->buildProbes = false;};

    pData->buildOrder[1] = std::make_pair(8, BWAPI::UnitTypes::Enum::Protoss_Pylon);
    pData->buildOrderExtension[1] = [](Data* pData) {std::cout << "BO-1\n";pData->buildProbes = true;};

    pData->buildOrder[2] = std::make_pair(11, BWAPI::UnitTypes::Enum::Protoss_Gateway);
    pData->buildOrderExtension[2] = [](Data* pData) {std::cout << "BO-2\n";};

    pData->buildOrder[3] = std::make_pair(12, BWAPI::UnitTypes::Enum::Protoss_Assimilator);
    pData->buildOrderExtension[3] = [](Data* pData) {std::cout << "BO-3\n";};

    pData->buildOrder[4] = std::make_pair(13, NULL);
    pData->buildOrderExtension[4] = [](Data* pData) {std::cout << "BO-4\n";};

    pData->buildOrder[5] = std::make_pair(14, BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core);
    pData->buildOrderExtension[5] = [](Data* pData) {std::cout << "BO-5\n"; Tools::SendProbesToGas(2);};

    pData->buildOrder[6] = std::make_pair(15, BWAPI::UnitTypes::Enum::Protoss_Pylon);
    pData->buildOrderExtension[6] = [](Data* pData) 
        {
            std::cout << "BO-6\n";
            Tools::SendProbesToGas(1);
            pData->buildArmy = true;
            pData->autoBuildPylon = true;
            pData->autoBuildGate = true;
        };

    pData->buildOrder[7] = std::make_pair(1000, NULL);   //1000 acts as an unreachable condition, marks the end of BO
}