#pragma once
#include "uimenu.h"
#include "Cell.h"
class MapMenu :
	public UIMenu
{
public:
	MapMenu(void);
	MapMenu(Cell* selectedCell);
	~MapMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};

