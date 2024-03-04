#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Data.h>
#include <format>

#include "BT.h"

StarterBot::StarterBot()
{
    pData = new Data();
    StarterBot::setupData();
    pData->currMinerals = 0;
    pData->currSupply = 0;
    pData->currProbes = 0;
    pData->thresholdSupply = 2;

    //Define build order
    pData->buildOrder[0] = std::make_pair(8, BWAPI::UnitTypes::Enum::Protoss_Pylon);
    pData->buildOrderExtension[0] = []() {std::cout << "BO-0\n";};
    pData->buildOrder[1] = std::make_pair(11, BWAPI::UnitTypes::Enum::Protoss_Gateway);
    pData->buildOrderExtension[1] = []() {std::cout << "BO-1\n";};
    pData->buildOrder[2] = std::make_pair(12, BWAPI::UnitTypes::Enum::Protoss_Assimilator);
    pData->buildOrderExtension[2] = []() {std::cout << "BO-2\n";};
    pData->buildOrder[3] = std::make_pair(13, NULL);
    pData->buildOrderExtension[3] = []() {std::cout << "BO-3\n";};
    pData->buildOrder[4] = std::make_pair(14, BWAPI::UnitTypes::Enum::Protoss_Cybernetics_Core);
    pData->buildOrderExtension[4] = []() {std::cout << "BO-4\n"; Tools::SendProbesToGas(2);};
    pData->buildOrder[5] = std::make_pair(15, BWAPI::UnitTypes::Enum::Protoss_Pylon);
    pData->buildOrderExtension[5] = []() {std::cout << "BO-5\n";Tools::SendProbesToGas(1);};
    pData->buildOrder[6] = std::make_pair(201, NULL);   //201 acts as an unreachable condition, marks the end of BO


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

    //Progress build order
    BT_DECO_CONDITION_BO* pBOCondition = new BT_DECO_CONDITION_BO("BOCondition", pMTRootSelector);
    BT_ACTION_BO* pBOAction = new BT_ACTION_BO("BOAction", pBOCondition);
    
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

    //std::cout << pData->currMinerals<<"\n";
    
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

void StarterBot::setupData() {
    for (int i = 0; i < Data::buildOrderMaxLength; ++i) {
        Data::buildOrderExtension[i] = []() {};
    }
}
