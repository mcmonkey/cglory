#include "StdAfx.h"
#include "CardCursor.h"
#include "PlayManager.h"


CardCursor::CardCursor(void)
{
}


CardCursor::~CardCursor(void)
{
}

CardCursor::CardCursor(Cell* c, int id)
{
	currCell = c;
	cardId = id;
	generalInit();
}

void CardCursor::generalInit()
{
	GameCursor::moveCursor(currCell->x, currCell->y);
}

void CardCursor::select()
{
	//PlayManager::getActivePlayer()->playCard(cardId, PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y));
	if(PlayManager::getActivePlayer()->playCard(cardId, PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y)))
	{
		InputManager::removeCatcher();
	}
}

bool CardCursor::catchKey(KeyState k)
{
	switch(k.keyCode)
	{
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
	}
	return GameCursor::catchKey(k);
}