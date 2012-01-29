#include "StdAfx.h"
#include "MapMenu.h"
#include "AllTerrainMenu.h"
#include "AllBuildingMenu.h"
#include "AllUnitMenu.h"

MapMenu::MapMenu(void)
{
}


MapMenu::~MapMenu(void)
{
}

MapMenu::MapMenu(Cell* selectedCell) : UIMenu(selectedCell)
{
	prevLoc = selectedCell->position;

	generalInit();

	setupSprites();
}

void MapMenu::setupOptions()
{
	addOption(L"Terrain", 0);
	addOption(L"Building", 1);
	addOption(L"Unit", 2);
	UIMenu::setupOptions();
}

void MapMenu::select(int selectedId)
{
	
	switch(selectedId)
	{
	case 0:
		//Terrain
		new AllTerrainMenu(currCell);
		break;
	case 1:
		//Building
		new AllBuildingMenu(currCell);
		break;
	case 2:
		//Unit
		new AllUnitMenu(currCell);
		break;
	}
	UIMenu::select(selectedId);
	
}