#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Data.h>
#include <format>

#include "BT.h"

StarterBot::StarterBot()
{
    pData = new Data();
    pData->currMinerals = 0;
    pData->currSupply = 0;
    pData->currProbes = 0;
    pData->thresholdSupply = 2;

    pData->buildProbes = true;
    pData->buildArmy = false;
    pData->autoBuildPylon = true;
    pData->autoBuildGate = false;

    pData->pylonIsUnderBuild = false;
    pData->gateIsUnderBuild = false;


    pData->wantedWorkersTotal = WANTED_WORKERS_TOTAL;

   
    //Construction of Macro Tree
    pMacroTree = new BT_DECORATOR("EntryPoint", nullptr);
    BT_DECO_REPEATER* pMTForeverRepeater = new BT_DECO_REPEATER("MTRepeatForever", pMacroTree, 0, true, false, true);
    BT_SELECTOR* pMTRootSelector = new BT_SELECTOR("MTRootSelector", pMTForeverRepeater, 5);

    //Send idle workers to work
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pMTRootSelector);

    //Build units according to general goal
    BT_SELECTOR* pBuildUnitsSelector = new BT_SELECTOR("BuildUnitsSelector", pMTRootSelector, 10);

    BT_DECO_CONDITION_BUILD_PROBE* pBuildProbeCondition = new BT_DECO_CONDITION_BUILD_PROBE("BuildProbeCondition", pBuildUnitsSelector);
    BT_ACTION_TRAIN_UNIT* pBuildProbeAction = new BT_ACTION_TRAIN_UNIT("BuildProbeAction", pBuildProbeCondition, BWAPI::UnitTypes::Enum::Protoss_Probe);

    //Build buildings according to general goal
    BT_SELECTOR* pBuildBuildingsSelector = new BT_SELECTOR("BuildBuildingsSelector", pMTRootSelector, 10);

    BT_DECO_CONDITION_BUILD_PYLON* pBuildPylonCondition = new BT_DECO_CONDITION_BUILD_PYLON("BuildPylonCondition", pBuildBuildingsSelector);
    BT_ACTION_BUILD_BUILDING* pBuildPylonAction = new BT_ACTION_BUILD_BUILDING("BuildPylonAction", pBuildPylonCondition, BWAPI::UnitTypes::Enum::Protoss_Pylon);
    
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
    
}

// Called on each frame of the game
void StarterBot::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();

    // Update pData 
    Tools::UpdateDataValues(pData);
    Tools::UpdateBuildingStatus(pData);

    
    // Run MacroTree
    if (pMacroTree != nullptr && pMacroTree->Evaluate(pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pMacroTree;
        pMacroTree = nullptr;
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