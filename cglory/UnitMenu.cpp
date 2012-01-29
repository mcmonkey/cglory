#include "StdAfx.h"
#include "UnitMenu.h"
#include "InputManager.h"
#include "SelectionCursor.h"
#include "AttackCursor.h"
#include "AmbushDirectionSelector.h"
#include "Terrain.h"
#include "BombardCursor.h"

UnitMenu::UnitMenu(void)
{
}

UnitMenu::UnitMenu(Unit* u) : UIMenu(u)
{
	generalInit();

	setupSprites();
}


UnitMenu::~UnitMenu(void)
{
}

void UnitMenu::setupOptions()
{
	Unit* u = (Unit*)gObj;

	//add names for each option and increment for each one
	bool e = u->isExhausted();

	if(e)
		addOption(L"End Turn", 6);

	addOption(L"Move", 0, !e && !u->hasMoved());
	addOption(L"Attack", 1, !e && !u->hasAttacked());
	if(u->canAmbush())
		addOption(L"Ambush", 2, !e && ((Terrain*)u->getCell()->objectAtLayer(CellLayers::Terrain))->grantsCover);
	if(u->canCapture())
		addOption(L"Capture", 3, !e && !u->hasAttacked() && ((Building*)u->getCell()->objectAtLayer(CellLayers::Building)) && ((Building*)u->getCell()->objectAtLayer(CellLayers::Building))->isEnemy(*u));
	if(u->canBombard())
		addOption(L"Bombard", 5, !e && !u->hasAttacked());
	if(u->hasMoved())
		addOption(L"End", 4, !e);
	
	UIMenu::setupOptions();
}

void UnitMenu::select(int selectedId)
{
	GameObject* gObj = this->gObj;
	switch(selectedId)
	{
	case 0:
		//Move
		//create a MovementCursor/SelectionCursor
		new SelectionCursor((Unit*)gObj);
		break;
	case 1:
		//Attack
		//create a AttackCursor
		new AttackCursor((Unit*)gObj);
		break;
	case 5:
		new BombardCursor((Unit*)gObj);
		break;
	case 2:
		new AmbushDirectionSelector((Unit*)gObj);
		break;
	case 4:
		((Unit*)gObj)->exhaust();
		InputManager::removeCatcher();
		break;
	case 3:

		InputManager::removeCatcher();
		((Unit*)gObj)->capture((Building*)gObj->getCell()->objectAtLayer(CellLayers::Building));
		break;
	case 6:
		InputManager::removeCatcher();
		PlayManager::advanceTurn();
		return;
	}
	UIMenu::select(selectedId);
}