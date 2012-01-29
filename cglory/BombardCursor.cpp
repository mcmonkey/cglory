#include "StdAfx.h"
#include "BombardCursor.h"
#include "InputManager.h"
#include "PlayManager.h"
#include <algorithm>

BombardCursor::BombardCursor(Unit* u) : AttackCursor(u)
{
}


BombardCursor::~BombardCursor(void)
{
}

void BombardCursor::select()
{
	//find the cell that we're at
	Cell* selectedCell = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);

	//find an r where r is a path to get us to where the selectedCell is
	vector<shared_ptr<CellPathNode>>::iterator r = find(cPN.begin(), cPN.end(), selectedCell);
	

	//did we find it?
	// Yep, found.
	Unit* u;
	if(r < cPN.end())
	{
		unit->bombard(selectedCell);
		//and pop the cursor from the InputManager catcher stack
		InputManager::removeCatcher();
		//and one more for good luck (and by good luck, I mean to pop the menu that called it
		//InputManager::removeCatcher();
		//and set the gCursor's position to where we put the unit
		InputManager::mainCursor->moveCursorAbs(selectedCell->x, selectedCell->y);
		//}
	}
	else
	{
		//do nothing for now
	}
}