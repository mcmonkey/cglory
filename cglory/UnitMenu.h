#pragma once
#include "UnitMenu.h"
#include "UIMenu.h"
#include "Unit.h"
class UnitMenu : public UIMenu
{
public:
	UnitMenu(void);
	UnitMenu(Unit* u);
	~UnitMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};

