#pragma once
#include "UIMenu.h"
#include "Terrain.h"
class TerrainMenu : public UIMenu
{
public:
	TerrainMenu(void);
	TerrainMenu(Terrain* t);
	~TerrainMenu(void);

	virtual void setupOptions();
	virtual void select(int selectedId);
};

