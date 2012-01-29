#pragma once
#include "uimenu.h"
#include "Cell.h"
class AllTerrainMenu :
	public UIMenu
{
public:
	AllTerrainMenu(void);
	AllTerrainMenu(Cell* selectedCell);
	~AllTerrainMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};

