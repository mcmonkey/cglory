#pragma once
#include "Cell.h"

// Used as a wrapper around a cost function, allowing a inheriting object to store information
// (couldn't easily pass member functions like Unit::visibilityTraveral, due to c++ being c++)
class TraversalCostHelper
{
public:
	virtual int cost(Cell* from, Cell* to) = 0;
};