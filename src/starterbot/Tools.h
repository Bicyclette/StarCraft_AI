#pragma once

#include <BWAPI.h>
#include "Data.h"

namespace Tools
{
    BWAPI::Unit GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units);
    BWAPI::Unit GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units);
    bool IsUnitInUnitset(BWAPI::Unit unit, const BWAPI::Unitset& units);

    int CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units);

    BWAPI::Unit GetUnitOfType(BWAPI::UnitType type);
    BWAPI::Unit GetDepot();

    bool BuildBuilding(BWAPI::UnitType type);
    bool MyBuildBuilding(BWAPI::UnitType type, Data* pData);

    void DrawUnitBoundingBoxes();
    void DrawUnitCommands();
    void DrawArmyAttentionRadius(BWAPI::Unitset, int radius);

    void SmartRightClick(BWAPI::Unit unit, BWAPI::Unit target);

    int GetUnusedSupply(bool inProgress = false);
    int GetTotalSupply(bool inProgress = false);

    void DrawUnitHealthBars();
    void DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset);

    void UpdateBuildingStatus(Data* pData);
    void UpdateDataValues(Data* pData);
    bool IsBuildingAvailable(BWAPI::UnitType type);
    bool UnitExists(BWAPI::UnitType type);
    bool BuildingExistsOrOrderToBuildGiven(BWAPI::UnitType type);

    void SendProbesToGas(int amount);
    void setGateRally(Data* pData);


    void sendUnitsTo(BWAPI::Position target);
    void setGateRallyPoints(BWAPI::Position target);
}