#pragma once
#include "uimenu.h"
#include "Cell.h"

class InGameOptions :
	public UIMenu
{
public:
	InGameOptions(Cell*);
	~InGameOptions(void);

	void setupOptions();
	void select(int);
};

