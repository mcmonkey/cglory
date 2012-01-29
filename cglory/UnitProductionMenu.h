#pragma once
#include "UIMenu.h"
#include "Building.h"
class UnitProductionMenu : public UIMenu
{
public:
	UnitProductionMenu(void);
	UnitProductionMenu(Building* b);
	~UnitProductionMenu(void);

	bool builtSomething;

	virtual void setupOptions();
	virtual void select(int selectedId);
};

