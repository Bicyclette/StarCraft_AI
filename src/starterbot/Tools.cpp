#include "Tools.h"
#include <format>

BWAPI::Unit Tools::GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units)
{
    BWAPI::Unit closestUnit = nullptr;

    for (auto& u : units)
    {
        if (!closestUnit || u->getDistance(p) < closestUnit->getDistance(p))
        {
            closestUnit = u;
        }
    }

    return closestUnit;
}

BWAPI::Unit Tools::GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units)
{
    if (!unit) { return nullptr; }
    return GetClosestUnitTo(unit->getPosition(), units);
}

int Tools::CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units)
{
    int sum = 0;
    for (auto& unit : units)
    {
        if (unit->getType() == type)
        {
            sum++;
        }
    }

    return sum;
}

BWAPI::Unit Tools::GetUnitOfType(BWAPI::UnitType type)
{
    // For each unit that we own
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == type && unit->isCompleted())
        {
            return unit;
        }
    }

    // If we didn't find a valid unit to return, make sure we return nullptr
    return nullptr;
}

BWAPI::Unit Tools::GetDepot()
{
    const BWAPI::UnitType depot = BWAPI::Broodwar->self()->getRace().getResourceDepot();
    return GetUnitOfType(depot);
}

// Attempt tp construct a building of a given type 
bool Tools::BuildBuilding(BWAPI::UnitType type)
{
    // Get the type of unit that is required to build the desired building
    BWAPI::UnitType builderType = type.whatBuilds().first;

    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    BWAPI::Unit builder = Tools::GetUnitOfType(builderType);
    if (!builder) { return false; }

    // Get a location that we want to build the building next to
    BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();

    // Ask BWAPI for a building location near the desired position for the type
    int maxBuildRange = 64;
    bool buildingOnCreep = type.requiresCreep();
    BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(type, desiredPos, maxBuildRange, buildingOnCreep);
    return builder->build(type, buildPos);
}

bool Tools::MyBuildBuilding(BWAPI::UnitType type, Data* pData) {
    // Find a worker that isn't on more important task
    BWAPI::Unit myWorker = NULL;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Probe && !unit->isGatheringGas() && unit->isCompleted()) {
            myWorker = unit;
            break;
        }
    }

    BWAPI::TilePosition buildPos;

    // Get a location that we want to build the building next to


    if (type == BWAPI::UnitTypes::Enum::Protoss_Pylon && pData->pylonPosList[pData->pylonPosStep] != BWAPI::TilePosition(0, 0)) {
        buildPos = pData->pylonPosList[pData->pylonPosStep];
        pData->pylonPosStep++;
        std::cout << "Pylon pos custom : " << buildPos;
    }
    else if (type == BWAPI::UnitTypes::Enum::Protoss_Gateway && pData->gatePosList[pData->gatePosStep] != BWAPI::TilePosition(0, 0)) {
        buildPos = pData->gatePosList[pData->gatePosStep];
        pData->gatePosStep++;
        std::cout << "Gate pos custom : " << buildPos;
    }
    else if (type == BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core && pData->cyberPosList[pData->cyberPosStep] != BWAPI::TilePosition(0, 0)) {
        buildPos = pData->cyberPosList[pData->cyberPosStep];
        pData->cyberPosStep++;
        std::cout << "Cyber pos custom : " << buildPos;
    }
    else {
        BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();
        int maxBuildRange = 64;
        buildPos = BWAPI::Broodwar->getBuildLocation(type, desiredPos, maxBuildRange, false);
    }

    std::cout << "Pos result: " << buildPos;
    return myWorker->build(type, buildPos);

}

void Tools::DrawUnitCommands()
{
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        const BWAPI::UnitCommand & command = unit->getLastCommand();

        // If the previous command had a ground position target, draw it in red
        // Example: move to location on the map
        if (command.getTargetPosition() != BWAPI::Positions::None)
        {
            BWAPI::Broodwar->drawLineMap(unit->getPosition(), command.getTargetPosition(), BWAPI::Colors::Red);
        }

        // If the previous command had a tile position target, draw it in red
        // Example: build at given tile position location
        if (command.getTargetTilePosition() != BWAPI::TilePositions::None)
        {
            BWAPI::Broodwar->drawLineMap(unit->getPosition(), BWAPI::Position(command.getTargetTilePosition()), BWAPI::Colors::Green);
        }

        // If the previous command had a unit target, draw it in red
        // Example: attack unit, mine mineral, etc
        if (command.getTarget() != nullptr)
        {
            BWAPI::Broodwar->drawLineMap(unit->getPosition(), command.getTarget()->getPosition(), BWAPI::Colors::White);
        }
    }
}

void Tools::DrawUnitBoundingBoxes()
{
    for (auto& unit : BWAPI::Broodwar->getAllUnits())
    {
        BWAPI::Position topLeft(unit->getLeft(), unit->getTop());
        BWAPI::Position bottomRight(unit->getRight(), unit->getBottom());
        BWAPI::Broodwar->drawBoxMap(topLeft, bottomRight, BWAPI::Colors::White);
    }
}

void Tools::SmartRightClick(BWAPI::Unit unit, BWAPI::Unit target)
{
    // if there's no valid unit, ignore the command
    if (!unit || !target) { return; }

    // Don't issue a 2nd command to the unit on the same frame
    if (unit->getLastCommandFrame() >= BWAPI::Broodwar->getFrameCount()) { return; }

    // If we are issuing the same type of command with the same arguments, we can ignore it
    // Issuing multiple identical commands on successive frames can lead to bugs
    if (unit->getLastCommand().getTarget() == target) { return; }
    
    // If there's nothing left to stop us, right click!
    unit->rightClick(target);
}

int Tools::GetUnusedSupply(bool inProgress)
{
    int unusedSupply = Tools::GetTotalSupply(inProgress) - BWAPI::Broodwar->self()->supplyUsed();
    return unusedSupply;
}

int Tools::GetTotalSupply(bool inProgress)
{
    // start the calculation by looking at our current completed supplyt
    int totalSupply = BWAPI::Broodwar->self()->supplyTotal();

    // if we don't want to calculate the supply in progress, just return that value
    if (!inProgress) { return totalSupply; }

    // if we do care about supply in progress, check all the currently constructing units if they will add supply
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // ignore units that are fully completed
        if (unit->isCompleted()) { continue; }

        // if they are not completed, then add their supply provided to the total supply
        totalSupply += unit->getType().supplyProvided();
    }

    // one last tricky case: if a unit is currently on its way to build a supply provider, add it
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // get the last command given to the unit
        const BWAPI::UnitCommand& command = unit->getLastCommand();

        // if it's not a build command we can ignore it
        if (command.getType() != BWAPI::UnitCommandTypes::Build) { continue; }

        // add the supply amount of the unit that it's trying to build
        totalSupply += command.getUnitType().supplyProvided();
    }

    return totalSupply;
}

void Tools::DrawUnitHealthBars()
{
    // how far up from the unit to draw the health bar
    int verticalOffset = -10;

    // draw a health bar for each unit on the map
    for (auto& unit : BWAPI::Broodwar->getAllUnits())
    {
        // determine the position and dimensions of the unit
        const BWAPI::Position& pos = unit->getPosition();
        int left = pos.x - unit->getType().dimensionLeft();
        int right = pos.x + unit->getType().dimensionRight();
        int top = pos.y - unit->getType().dimensionUp();
        int bottom = pos.y + unit->getType().dimensionDown();

        // if it's a resource, draw the resources remaining
        if (unit->getType().isResourceContainer() && unit->getInitialResources() > 0)
        {
            double mineralRatio = (double)unit->getResources() / (double)unit->getInitialResources();
            DrawHealthBar(unit, mineralRatio, BWAPI::Colors::Cyan, 0);
        }
        // otherwise if it's a unit, draw the hp 
        else if (unit->getType().maxHitPoints() > 0)
        {
            double hpRatio = (double)unit->getHitPoints() / (double)unit->getType().maxHitPoints();
            BWAPI::Color hpColor = BWAPI::Colors::Green;
            if (hpRatio < 0.66) hpColor = BWAPI::Colors::Orange;
            if (hpRatio < 0.33) hpColor = BWAPI::Colors::Red;
            DrawHealthBar(unit, hpRatio, hpColor, 0);
            
            // if it has shields, draw those too
            if (unit->getType().maxShields() > 0)
            {
                double shieldRatio = (double)unit->getShields() / (double)unit->getType().maxShields();
                DrawHealthBar(unit, shieldRatio, BWAPI::Colors::Blue, -3);
            }
        }
    }
}

void Tools::DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset)
{
    int verticalOffset = -10;
    const BWAPI::Position& pos = unit->getPosition();

    int left = pos.x - unit->getType().dimensionLeft();
    int right = pos.x + unit->getType().dimensionRight();
    int top = pos.y - unit->getType().dimensionUp();
    int bottom = pos.y + unit->getType().dimensionDown();

    int ratioRight = left + (int)((right - left) * ratio);
    int hpTop = top + yOffset + verticalOffset;
    int hpBottom = top + 4 + yOffset + verticalOffset;

    BWAPI::Broodwar->drawBoxMap(BWAPI::Position(left, hpTop), BWAPI::Position(right, hpBottom), BWAPI::Colors::Grey, true);
    BWAPI::Broodwar->drawBoxMap(BWAPI::Position(left, hpTop), BWAPI::Position(ratioRight, hpBottom), color, true);
    BWAPI::Broodwar->drawBoxMap(BWAPI::Position(left, hpTop), BWAPI::Position(right, hpBottom), BWAPI::Colors::Black, false);

    int ticWidth = 3;

    for (int i(left); i < right - 1; i += ticWidth)
    {
        BWAPI::Broodwar->drawLineMap(BWAPI::Position(i, hpTop), BWAPI::Position(i, hpBottom), BWAPI::Colors::Black);
    }
}

void Tools::UpdateBuildingStatus(Data* pData) {
    pData->pylonIsUnderBuild = false;
    pData->gateIsUnderBuild = false;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Pylon && !unit->isCompleted())
        {
            pData->pylonIsUnderBuild = true;
        }

        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Gateway && !unit->isCompleted())
        {
            pData->gateIsUnderBuild = true;
        }
    }
}

void Tools::UpdateDataValues(Data* pData) {
    pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    pData->currGas = BWAPI::Broodwar->self()->gas();
    pData->currSupply = BWAPI::Broodwar->self()->supplyUsed();
    pData->totalSupply = BWAPI::Broodwar->self()->supplyTotal();


    int probes = 0;
    int probesOnGas = 0;
    int gates = 0;

    BWAPI::Unitset armyAtBase = BWAPI::Unitset();
    BWAPI::Unitset armyAtRally = BWAPI::Unitset();

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        if (unit->getType().isWorker())
        {
            probes++;
            if (unit->isGatheringGas()) {
                probesOnGas++;
            }
        }

        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Gateway) 
        {
            gates++;
        }

        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Zealot) 
        {
            if (unit->getDistance(pData->rallyPosition) < 500)
			{
				armyAtRally.insert(unit);
            }
            else if (unit->getDistance(pData->basePosition) < 600) {
				armyAtBase.insert(unit);
            }
		}

        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Dragoon)
        {
            if (unit->getDistance(pData->rallyPosition) < 500)
			{
				armyAtRally.insert(unit);
            }
            else if (unit->getDistance(pData->basePosition) < 500) {
                armyAtBase.insert(unit);
            }

        }

    }
    // this value must be MORE than the value defined in CONDITIONS_BCK sendTroopsCondition function
    if (armyAtBase.size() > 6) {
        // if we have enough units at base, send them to the rally point
        pData->sendingToRally = false;
	}

    // same argument here
    if (armyAtRally.size() > 6) {
		// if we have enough units at rally point, send them to the enemy
        pData->attacking = false;
    }

    pData->currProbes = probes;
    pData->currGates = gates;
    pData->thresholdSupply = 2 + gates * 6;
    pData->probesOnGas = probesOnGas;
    pData->armyAtBase = armyAtBase;
    pData->armyAtRally = armyAtRally;
 }

bool Tools::IsBuildingAvailable(BWAPI::UnitType type) {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == type && unit->isCompleted() && !unit->isTraining() && !unit->isUpgrading() && !unit->isResearching())
        {
            return true;
        }
    }
    return false;
}

bool Tools::UnitExists(BWAPI::UnitType type) {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == type && unit->isCompleted())
        {
            return true;
        }
    }
    return false;
}

bool Tools::BuildingExistsOrOrderToBuildGiven(BWAPI::UnitType type) {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == type) { return true; }
        
        const BWAPI::UnitCommand& command = unit->getLastCommand();

        if (command.getType() != BWAPI::UnitCommandTypes::Build) { continue; }

        if (command.getUnitType() == type) { return true; };
    }

    return false;
}

void Tools::SendProbesToGas(int amount) {
    const BWAPI::Unit myAssimilator = Tools::GetUnitOfType(BWAPI::UnitTypes::Enum::Protoss_Assimilator);

    if (myAssimilator)
    {
        const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
        for (auto& unit : myUnits)
        {
            if (unit->getType().isWorker() && (unit->isIdle() || unit->isGatheringMinerals()))
            {
                unit->rightClick(myAssimilator);
                amount--;
            }

            if (amount <= 0) return;
        }
    }

    std::cout << "Not enough probes were sent to gas";
}

void Tools::sendUnitsTo(BWAPI::Position target) {
    const std::list<BWAPI::UnitType> attackUnits = {BWAPI::UnitTypes::Enum::Protoss_Zealot, BWAPI::UnitTypes::Enum::Protoss_Dragoon};

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();

    for (auto& unit : myUnits)
    {
        if (unit->isCompleted() && std::find(attackUnits.begin(), attackUnits.end(), unit->getType()) != attackUnits.end())
        {
            unit->attack(target, false);
        }
    }
}

void Tools::setGateRallyPoints(BWAPI::Position target) {
    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();

    for (auto& unit : myUnits) {
        if (unit->getType() == BWAPI::UnitTypes::Enum::Protoss_Gateway) {
            unit->setRallyPoint(target);
        }
    }
}