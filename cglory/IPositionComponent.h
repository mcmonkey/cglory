#pragma once
#include "gameobjectcomponent.h"
#include "Cell.h"

class IPositionComponent :
	public cglory::game::IGameObjectComponent<1>
{
public:
	virtual Cell* getCell() = 0;
	virtual void setCell(Cell*) = 0;

	virtual bool tryGetCell(Cell**) = 0;
};

