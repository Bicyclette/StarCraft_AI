#include "Data.h"

std::pair<int, BWAPI::UnitType> Data::buildOrder[Data::buildOrderMaxLength];
std::function<void()> Data::buildOrderExtension[Data::buildOrderMaxLength];