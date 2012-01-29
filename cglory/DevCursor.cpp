#include "StdAfx.h"
#include "DevCursor.h"
#include "InputManager.h"
#include "PlayManager.h"
#include "MapMenu.h"

DevCursor::DevCursor(void)
{
}


DevCursor::~DevCursor(void)
{
}


bool DevCursor::catchKey(KeyState k)
{
	switch(k.keyCode)
	{
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
	}
	return GameCursor::catchKey(k);
}

void DevCursor::select()
{
	Cell* selectedCell = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);
	new MapMenu(selectedCell);
}

void DevCursor::draw()
{
	GameCursor::draw();
}