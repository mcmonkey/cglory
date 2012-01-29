#include "StdAfx.h"
#include "ForceReplaceCursor.h"
#include "InputManager.h"
#include "PlayManager.h"

ForceReplaceCursor::ForceReplaceCursor(GameObject* g) : GameCursor()
{
	placing = g;
}

bool ForceReplaceCursor::catchKey(KeyState k)
{
	switch(k.keyCode)
	{
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
	}
	return GameCursor::catchKey(k);
}

void ForceReplaceCursor::draw()
{
	GameCursor::draw();
	GameSprite g = *placing->getGSprite();
	Cell* c = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);
	g.position.x = c->position.x;
	g.position.y = c->position.y;
	addToDraw(g);
}

void ForceReplaceCursor::select()
{
	Cell* c = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);
	GameObject* g = placing->copy();
	c->replaceGameObject(*g);
}

ForceReplaceCursor::~ForceReplaceCursor(void)
{
	delete placing;
}
