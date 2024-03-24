#include "BT_ACTION_EXPLORE.h"
#include <random>
#include <Data.h>


BT_ACTION_EXPLORE::BT_ACTION_EXPLORE(std::string name, BT_NODE* parent)
	: BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_EXPLORE::Evaluate(void* data)
{
	return ReturnState(Explore(data));
}

std::string BT_ACTION_EXPLORE::GetDescription()
{
	return "SENDS ATTACKING UNITS EXPLORING ON RANDOM AREAS";
}
int getRandomNumber(int x, int y) {
	// Use a random device to seed the random number generator
	std::random_device rd;
	// Create a random number engine
	std::mt19937 gen(rd());
	// Define the distribution for the random numbers
	std::uniform_int_distribution<> distrib(x, y);
	// Generate a random number within the specified range and return it
	return distrib(gen);
}

BWAPI::Position getRandomPosition() {
	int maxX = 3000;
	int maxY = 4000;
	return BWAPI::Position(getRandomNumber(0, maxX), getRandomNumber(0, maxY));
}

BT_NODE::State BT_ACTION_EXPLORE::Explore(void* data)
{
	Data* pData = (Data*)data;
	

	for (BWAPI::Unit unit : pData->armyAttacking) {
		if (!unit->getOrder() == BWAPI::Orders::Enum::Move) {
			BWAPI::Position target = getRandomPosition();
			while (!unit->hasPath(target)) {
				target = getRandomPosition();
			}
			unit->move(target);
			return BT_NODE::State::SUCCESS;
		}
	}
	return BT_NODE::State::FAILURE;
}

