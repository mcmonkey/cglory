#include "StdAfx.h"
#include "AllUnitMenu.h"
#include "InformationStorage.h"
#include "InputManager.h"
#include "ForceReplaceCursor.h"
#include "Unit.h"
#include "PlayManager.h"
#include <algorithm>

AllUnitMenu::AllUnitMenu(void)
{
}


AllUnitMenu::~AllUnitMenu(void)
{
}

AllUnitMenu::AllUnitMenu(Cell* selectedCell) : UIMenu(selectedCell)
{
	prevLoc = selectedCell->position;

	generalInit();

	setupSprites();
}

void AllUnitMenu::setupOptions()
{
	//go through all the names in the buildingTypes in storage and list them
	for_each(InformationStorage::unitTypes.begin(), InformationStorage::unitTypes.end(), [&](pair<int, UnitInfo> kvp){
		addOption(Utility::widen(kvp.second.name), kvp.first);
	});
	UIMenu::setupOptions();
}

void AllUnitMenu::select(int selectedId)
{
	if(InformationStorage::unitTypes.end() != InformationStorage::unitTypes.find(selectedId))
	{
		
		Unit* u = InformationStorage::getUnit(selectedId);
		u->setOwner(PlayManager::getActivePlayer());
		new ForceReplaceCursor(u);
	}
	else
	{
		//then we're supposed to exit.
		//pop the menu
		UIMenu::select(selectedId);
	}
}
