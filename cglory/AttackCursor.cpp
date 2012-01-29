#include "StdAfx.h"
#include "AttackCursor.h"
#include <algorithm>
#include "PlayManager.h"
#include "InputManager.h"


AttackCursor::AttackCursor(void)
{
}


AttackCursor::~AttackCursor(void)
{
}

AttackCursor::AttackCursor(Unit * u)
{
	unit = u;
	generalInit();
}

void AttackCursor::generalInit()
{
	//then move to where the unit is
	GameCursor::moveCursor(unit->getCell()->x, unit->getCell()->y);
	
	// Get a list of areas we can travel to
	//cPN = unit->cellsCanTravelTo();
	cPN = unit->cellsCanHit();
	Utility::spriteFactory(&available, L"range.png");
	available.position.z = ZOrdering::MapOverlay;
}

bool AttackCursor::catchKey(KeyState k)
{
	switch(k.keyCode)
	{
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
	}
	return GameCursor::catchKey(k);
}

void AttackCursor::select()
{
	
	//find the cell that we're at
	Cell* selectedCell = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);

	//find an r where r is a path to get us to where the selectedCell is
	vector<shared_ptr<CellPathNode>>::iterator r = find(cPN.begin(), cPN.end(), selectedCell);
	

	//did we find it?
	// Yep, found.
	Unit* u;
	if(r < cPN.end() && (u = (Unit*)selectedCell->objectAtLayer(CellLayers::Unit)) && u->getOwner()->isEnemy(*unit->getOwner()) && u->visibleTo(*unit->getOwner()))
	{
		unit->attack(u);
		//and pop the cursor from the InputManager catcher stack
		InputManager::removeCatcher();
		//and one more for good luck (and by good luck, I mean to pop the menu that called it
		//InputManager::removeCatcher();
		//and set the gCursor's position to where we put the unit
		//InputManager::mainCursor->moveCursorAbs(selectedCell->x, selectedCell->y);
		//}
	}
	else
	{
		//do nothing for now
	}
}

void AttackCursor::draw()
{
	GameCursor::draw();
	for(vector<shared_ptr<CellPathNode>>::iterator i = cPN.begin(); i < cPN.end(); i++)
	{
		available.position.x = (*i)->cell->position.x;
		available.position.y = (*i)->cell->position.y;
		addToDraw(available);
	}

}