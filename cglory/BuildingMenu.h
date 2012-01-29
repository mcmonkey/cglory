#pragma once
#include "UIMenu.h"
#include "Building.h"

class BuildingMenu : public UIMenu
{
public:
	BuildingMenu(void);
	BuildingMenu(Building* b);
	~BuildingMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};


