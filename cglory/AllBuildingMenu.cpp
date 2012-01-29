#include "StdAfx.h"
#include "AllBuildingMenu.h"
#include "Utility.h"
#include "InformationStorage.h"
#include "InputManager.h"
#include "Building.h"
#include "PlayManager.h"
#include "ForceReplaceCursor.h"
#include <algorithm>

AllBuildingMenu::AllBuildingMenu(void)
{
}


AllBuildingMenu::~AllBuildingMenu(void)
{
}

AllBuildingMenu::AllBuildingMenu(Cell* selectedCell) : UIMenu(selectedCell)
{
	prevLoc = selectedCell->position;

	generalInit();

	setupSprites();
}

void AllBuildingMenu::setupOptions()
{
	//go through all the names in the buildingTypes in storage and list them
	for_each(InformationStorage::buildingTypes.begin(), InformationStorage::buildingTypes.end(), [&](pair<int, BuildingInfo> kvp){
		addOption(Utility::widen(kvp.second.name), kvp.first);
	});
	UIMenu::setupOptions();
}

void AllBuildingMenu::select(int selectedId)
{
	if(InformationStorage::buildingTypes.end() != InformationStorage::buildingTypes.find(selectedId))
	{
		//otherwise, replace the current terrain with the new one
		Building* b = InformationStorage::getBuilding(selectedId);
		b->setOwner(PlayManager::getActivePlayer());
		new ForceReplaceCursor(b);
	}
	else
		UIMenu::select(selectedId);
}