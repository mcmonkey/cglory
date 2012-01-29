#include "StdAfx.h"
#include "SelectionCursor.h"
#include <algorithm>
#include "PlayManager.h"
#include "InputManager.h"

SelectionCursor::SelectionCursor(void)
{
}


SelectionCursor::~SelectionCursor(void)
{
}

SelectionCursor::SelectionCursor(Unit* u)
{
	unit = u;
	generalInit();
}

void SelectionCursor::generalInit()
{
	//then move to where the unit is
	GameCursor::moveCursor(unit->getCell()->x, unit->getCell()->y);
	
	// Get a list of areas we can travel to
	cPN = unit->cellsCanTravelTo();
	Utility::spriteFactory(&available, L"available.png");
	available.position.z = ZOrdering::MapOverlay;
}

void SelectionCursor::moveCursor(float x, float y)
{
	GameCursor::moveCursor(x, y);
	
	Cell* selectedCell = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);

	//find an r where r is a path to get us to where the selectedCell is
	vector<shared_ptr<CellPathNode>>::iterator r = find(cPN.begin(), cPN.end(), selectedCell);
	
	if(r < cPN.end())
	{
		currentPath = Map::buildForwardPath(*r);
	}
	else
	{
		currentPath.clear();
	}

}
void SelectionCursor::select()
{
	if(currentPath.size() > 0)
	{
		
		InputManager::mainCursor->moveCursorAbs(tilePos.x, tilePos.y);
		// Attempt to
		//move the unit to the cell
		// Do nothing if failure.
		unit->followPath(currentPath);
		//and pop the cursor from the InputManager catcher stack
		InputManager::removeCatcher();
		//and one more for good luck (and by good luck, I mean to pop the menu that called it
		//InputManager::removeCatcher();
	}

}

void SelectionCursor::draw()
{
	GameCursor::draw();
	for(auto i = cPN.begin(); i < cPN.end(); i++)
	{
		available.position.x = (*i)->cell->position.x;
		available.position.y = (*i)->cell->position.y;
		addToDraw(available);
	}
	for(auto i = currentPath.begin(); i < currentPath.end(); i++)
	{
		GameSprite g = SpriteHelper::pathMarker;
		g.position = (*i)->position;
		g.position.z = ZOrdering::MapOverlay - .1f;
		addToDraw(g);
	}

}
