#pragma once
#include "gamecursor.h"
class CardCursor :
	public GameCursor
{
public:
	CardCursor(void);
	~CardCursor(void);
	CardCursor(Cell* c, int id);

	int cardId;
	Cell* currCell;

	void generalInit();
	void select();
	virtual bool catchKey(KeyState);
};

