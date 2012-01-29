#include "StdAfx.h"
#include "TerrainMenu.h"
#include "PlayManager.h"
#include "InputManager.h"
#include "InGameOptions.h"

TerrainMenu::TerrainMenu(void)
{
}

TerrainMenu::TerrainMenu(Terrain* t) : UIMenu(t)
{
	gObj = t;

	generalInit();

	setupSprites();
}


TerrainMenu::~TerrainMenu(void)
{
}

void TerrainMenu::setupOptions()
{
	//addOption(L"Construct", 0);
	addOption(L"End Turn", 1);
	addOption(L"Options", 3);
	UIMenu::setupOptions();
}

void TerrainMenu::select(int selectedId)
{

	switch(selectedId)
	{
	case 0:
		//Construct
		//new BuildingProductionMenu((Terrain*)gObj);
		break;
	case 1:
		//first pop this menu since we're switching turns
		InputManager::removeCatcher();
		//then advance the turns
		PlayManager::advanceTurn();
		break;
	case 3:
		Cell* c = gObj->getCell();
		InputManager::removeCatcher();
		new InGameOptions(c);
		break;
	}

	UIMenu::select(selectedId);
}
