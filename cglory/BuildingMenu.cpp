#include "StdAfx.h"
#include "BuildingMenu.h"
#include "UnitProductionMenu.h"
#include "PlayManager.h"
#include "InputManager.h"


BuildingMenu::BuildingMenu(void)
{
}

BuildingMenu::BuildingMenu(Building* b) : UIMenu(b)
{

	gObj = b;

	generalInit();

	setupSprites();
}


BuildingMenu::~BuildingMenu(void)
{
}

void BuildingMenu::setupOptions()
{
	//set up the options
	addOption(L"Build", 0);
	UIMenu::setupOptions();
}

void BuildingMenu::select(int selectedId)
{

	switch(selectedId)
	{
	case 0:
		//build
		new UnitProductionMenu((Building*)gObj);
		break;
	}

	UIMenu::select(selectedId);
	
}