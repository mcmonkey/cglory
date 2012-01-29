#pragma once
#include "UIMenu.h"
#include "Cell.h"
class AllBuildingMenu : public UIMenu
{
public:
	AllBuildingMenu(void);
	AllBuildingMenu(Cell* selectedCell);
	~AllBuildingMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};

