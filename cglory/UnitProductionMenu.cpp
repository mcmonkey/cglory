#include "StdAfx.h"
#include "UnitProductionMenu.h"
#include "UnitInfo.h"
#include "InformationStorage.h"
#include "InputManager.h"
#include <algorithm>

UnitProductionMenu::UnitProductionMenu(void)
{
}

UnitProductionMenu::UnitProductionMenu(Building* b):UIMenu(b)
{
	gObj = b;
	builtSomething = false;

	generalInit();

	setupSprites();
}

UnitProductionMenu::~UnitProductionMenu(void)
{
}

void UnitProductionMenu::setupOptions()
{
	UnitInfo uI;
	for(int i = 0; i < ((Building*)gObj)->availableProduction.size(); i++)
	{
			uI = InformationStorage::unitTypes[((Building*)gObj)->availableProduction.at(i)];
			addOption(Utility::widen(uI.name),((Building*)gObj)->availableProduction.at(i), uI.cost < ((Building*)gObj)->getOwner()->glory);
	}
	UIMenu::setupOptions();
}

void UnitProductionMenu::select(int selectedId)
{
	if(((Building*)gObj)->availableProduction.end() != find(((Building*)gObj)->availableProduction.begin(), ((Building*)gObj)->availableProduction.end(), selectedId))
	{
		//if the optionSelection isn't the last one in the list, then the player tried to build a unit

		//Check if the player has enough glory. If so, build the unit
		if(((Building*)gObj)->getOwner()->glory >= InformationStorage::unitTypes[selectedId].cost)
		{
			((Building*)gObj)->produce(selectedId);
			//we've built a unit, so have the boolean represent that
			builtSomething = true;
			InputManager::removeCatcher();
			InputManager::removeCatcher();
		}
	}
	else
		UIMenu::select(selectedId);
	
}
