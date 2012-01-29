#pragma once
#include "uimenu.h"
#include "Cell.h"
class AllUnitMenu :
	public UIMenu
{
public:
	AllUnitMenu(void);
	AllUnitMenu(Cell* selectedCell);
	~AllUnitMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};

