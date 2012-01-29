#include "StdAfx.h"
#include "InGameOptions.h"

InGameOptions::InGameOptions(Cell* t) : UIMenu(t)
{
	generalInit();
	
	setupSprites();
}


InGameOptions::~InGameOptions(void)
{
}

void InGameOptions::setupOptions()
{
	addOption(L"Back", -1);
	addOption(L"Quit Game", 0);
	addOption(L"Settings", 1, false);
}

void InGameOptions::select(int id)
{
	switch(id)
	{
	case 0:
		PlayManager::gotoMainMenu();
		break;
	case 1:;
		//nothng;
	}
	UIMenu::select(id);
}
