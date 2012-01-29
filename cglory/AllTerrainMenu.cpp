#include "StdAfx.h"
#include "AllTerrainMenu.h"
#include "InformationStorage.h"
#include "Utility.h"
#include "InputManager.h"
#include "ForceReplaceCursor.h"
#include <algorithm>

AllTerrainMenu::AllTerrainMenu(void)
{
}


AllTerrainMenu::~AllTerrainMenu(void)
{
}

AllTerrainMenu::AllTerrainMenu(Cell* selectedCell) : UIMenu(selectedCell)
{
	prevLoc = selectedCell->position;

	generalInit();

	setupSprites();
}

void AllTerrainMenu::setupOptions()
{
	//go through all the names in the buildingTypes in storage and list them
	for_each(InformationStorage::terrainTypes.begin(), InformationStorage::terrainTypes.end(), [&](pair<int, TerrainInfo> kvp){
		addOption(Utility::widen(kvp.second.name), kvp.first);
	});
	UIMenu::setupOptions();
}

void AllTerrainMenu::select(int selectedId)
{
	if(InformationStorage::terrainTypes.end() != InformationStorage::terrainTypes.find(selectedId))
	{
		//then we're supposed to exit.
		//pop the menu
		new ForceReplaceCursor(InformationStorage::getTerrain(selectedId));
	}
	else
	{
		UIMenu::select(selectedId);
	}
}