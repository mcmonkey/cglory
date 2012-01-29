#pragma once
#include "titlemenu.h"
#include <map>

class MapSelectionMenu :
	public TitleMenu
{
public:
	map<int, string> pathNames;

public:
	virtual void setupOptions();
	virtual void select(int);

	MapSelectionMenu(void);
	~MapSelectionMenu(void);
};

