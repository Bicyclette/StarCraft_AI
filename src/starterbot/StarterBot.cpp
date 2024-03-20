#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Data.h>
#include <format>
#include <BuildOrder.h>

#include "BT.h"

StarterBot::StarterBot()
{
    pData = new Data();
    pData->currMinerals = 0;
    pData->currSupply = 0;
    pData->currProbes = 0;
    pData->thresholdSupply = 2;
    pData->wantedProbesOnGas = 0;
    pData->probesOnGas = 0;

    //Following line left as an example on how to use waitForCondition
    //pData->waitForConditionList.push_back(WaitForCondition(&mineralsHigherThan100, [](void* pData) {std::cout << "Minerals above 100";}));

    //Define build order
    setupBaseBuildOrder(pData);
    setUpOneBaseAllIn(pData);

    //Construction of Macro Tree
    pMacroTree = new BT_DECORATOR("EntryPoint", nullptr);
    BT_DECO_REPEATER* pMTForeverRepeater = new BT_DECO_REPEATER("MTRepeatForever", pMacroTree, 0, true, false, true);
    BT_SELECTOR* pMTRootSelector = new BT_SELECTOR("MTRootSelector", pMTForeverRepeater, 15);

    BT_DECO_CONDITION* pSendTroopsCondition = new BT_DECO_CONDITION("SendTroopsCondition", pMTRootSelector, &sendTroopsCondition);
    BT_ACTION_SEND_TROOPS* pSendTroopsAction = new BT_ACTION_SEND_TROOPS("SendTroopsAction", pSendTroopsCondition);

    BT_DECO_CONDITION* pAttackCondition = new BT_DECO_CONDITION("AttackCondition", pMTRootSelector, &attackTroopsCondition);
    BT_ACTION_ATTACK_TROOPS* pAttackAction = new BT_ACTION_ATTACK_TROOPS("AttackAction", pAttackCondition);

    //Send idle workers to work
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pMTRootSelector);
    BT_DECO_CONDITION* pSendWorkersToGasCondition = new BT_DECO_CONDITION("SendWorkersToGasCondition", pMTRootSelector, &sendWorkersToGasCondition);
    BT_ACTION_SEND_WORKERS_TO_GAS* pSendWorkersToGasAction = new BT_ACTION_SEND_WORKERS_TO_GAS("SendWorkersToGasAction", pSendWorkersToGasCondition);

    //Build units according to general goal
    BT_SELECTOR* pBuildUnitsSelector = new BT_SELECTOR("BuildUnitsSelector", pMTRootSelector, 10);

    BT_DECO_CONDITION* pBuildProbeCondition = new BT_DECO_CONDITION("BuildProbeCondition", pBuildUnitsSelector, &buildProbeCondition);
    BT_ACTION_TRAIN_UNIT* pBuildProbeAction = new BT_ACTION_TRAIN_UNIT("BuildProbeAction", pBuildProbeCondition, BWAPI::UnitTypes::Enum::Protoss_Probe);

    BT_DECO_CONDITION* pBuildDragoonCondition = new BT_DECO_CONDITION("BuildDragoonCondition", pBuildUnitsSelector, &buildDragoonCondition);
    BT_ACTION_TRAIN_UNIT* pBuildDragoonAction = new BT_ACTION_TRAIN_UNIT("BuildDragoonAction", pBuildDragoonCondition, BWAPI::UnitTypes::Enum::Protoss_Dragoon);

    BT_DECO_CONDITION* pBuildZealotCondition = new BT_DECO_CONDITION("BuildZealotCondition", pBuildUnitsSelector, &buildZealotCondition);
    BT_ACTION_TRAIN_UNIT* pBuildZealotAction = new BT_ACTION_TRAIN_UNIT("BuildZealotAction", pBuildZealotCondition, BWAPI::UnitTypes::Enum::Protoss_Zealot);

    //Build buildings according to general goal
    BT_SELECTOR* pBuildBuildingsSelector = new BT_SELECTOR("BuildBuildingsSelector", pMTRootSelector, 10);

    BT_DECO_CONDITION* pBuildPylonCondition = new BT_DECO_CONDITION("BuildPylonCondition", pBuildBuildingsSelector, &buildPylonCondition);
    BT_ACTION_BUILD_BUILDING* pBuildPylonAction = new BT_ACTION_BUILD_BUILDING("BuildPylonAction", pBuildPylonCondition, BWAPI::UnitTypes::Enum::Protoss_Pylon);

    BT_DECO_CONDITION* pBuildAssimilatorCondition = new BT_DECO_CONDITION("BuildAssimilatorCondition", pBuildBuildingsSelector, &buildAssimilatorCondition);
    BT_ACTION_BUILD_BUILDING* pBuildAssimilatorAction = new BT_ACTION_BUILD_BUILDING("BuildAssimilatorAction", pBuildAssimilatorCondition, BWAPI::UnitTypes::Enum::Protoss_Assimilator);

    BT_DECO_CONDITION* pBuildGateCondition = new BT_DECO_CONDITION("BuildGateCondition", pBuildBuildingsSelector, &buildGateCondition);
    BT_ACTION_BUILD_BUILDING* pBuildgateAction = new BT_ACTION_BUILD_BUILDING("BuildGateAction", pBuildGateCondition, BWAPI::UnitTypes::Enum::Protoss_Gateway);

    //Progress build order
    BT_DECO_CONDITION_BO* pBOCondition = new BT_DECO_CONDITION_BO("BOCondition", pMTRootSelector);
    BT_ACTION_BO* pBOAction = new BT_ACTION_BO("BOAction", pBOCondition);

    //Research
    BT_SELECTOR* pResearchSelector = new BT_SELECTOR("ResearchSelector", pMTRootSelector, 10);

    BT_DECO_CONDITION* pResearchSingularityChargeCondition = new BT_DECO_CONDITION("ResearchSingularityChargeCondition", pResearchSelector, upgradeSingularityChargeCondition);
    BT_ACTION_UPGRADE* pResearchSingularityChargeAction = new BT_ACTION_UPGRADE("ResearchSingularityChargeAction",
        pResearchSingularityChargeCondition, BWAPI::UpgradeTypes::Enum::Singularity_Charge);
    
}


// Called when the bot starts!
void StarterBot::onStart()
{
    // Set our BWAPI options here    
    BWAPI::Broodwar->setLocalSpeed(10);
    BWAPI::Broodwar->setFrameSkip(0);

    // Enable the flag that tells BWAPI top let users enter input while bot plays
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

    // Call MapTools OnStart
    m_mapTools.onStart();

    //Bwem
    //BWEM::Map::Instance().Initialize(BWAPI::BroodwarPtr);

    const std::deque<BWAPI::TilePosition> startLocations = BWAPI::Broodwar->getStartLocations();

    if (startLocations[0] == BWAPI::Broodwar->self()->getStartLocation()) {
        pData->enemyPosition = BWAPI::Position(startLocations[1]);
        pData->basePosition = BWAPI::Position(startLocations[0]);
    }
    else {
        pData->enemyPosition = BWAPI::Position(startLocations[0]);
        pData->basePosition = BWAPI::Position(startLocations[1]);
    }

    pData->rallyPosition = (pData->basePosition + pData->enemyPosition * 3) / 4;
}

// Called on each frame of the game
void StarterBot::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();

    // Update pData 
    Tools::UpdateDataValues(pData);
    Tools::UpdateBuildingStatus(pData);

    //pData->show_info();


    // Run MacroTree
    if (pMacroTree != nullptr && pMacroTree->Evaluate(pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pMacroTree;
        pMacroTree = nullptr;
    }


    // Test all of our waiting conditions
    auto it = pData->waitForConditionList.begin();
    while (it != pData->waitForConditionList.end()) {

        if (it->evaluate(pData)) {
            // Erase the current element
            it = pData->waitForConditionList.erase(it);
        }
        else {
            ++it;
        }
    }

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();
}

// Draw some relevent information to the screen to help us debug the bot
void StarterBot::drawDebugInformation()
{
    BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), "Hello, World!\n");
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever the game ends and tells you if you won or not
void StarterBot::onEnd(bool isWinner)
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";
}

// Called whenever a unit is destroyed, with a pointer to the unit
void StarterBot::onUnitDestroy(BWAPI::Unit unit)
{

}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void StarterBot::onUnitMorph(BWAPI::Unit unit)
{
	
}

// Called whenever a text is sent to the game by a user
void StarterBot::onSendText(std::string text) 
{ 
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void StarterBot::onUnitCreate(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit finished construction, with a pointer to the unit
void StarterBot::onUnitComplete(BWAPI::Unit unit)
{
    
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void StarterBot::onUnitShow(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void StarterBot::onUnitHide(BWAPI::Unit unit)
{ 
	
}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void StarterBot::onUnitRenegade(BWAPI::Unit unit)
{ 
	
}

