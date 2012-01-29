#pragma once
#include "GameCursor.h"
#include "Unit.h"
#include "CellPathNode.h"

class SelectionCursor : public GameCursor
{
public:
	SelectionCursor(void);
	~SelectionCursor(void);
	SelectionCursor(Unit* u);


	Unit* unit;
	GameSprite available;

	vector<shared_ptr<CellPathNode>>	cPN;			// Area available to move in.
	vector<Cell*>						currentPath;	// current path to follow.

	void generalInit();
	void select();
	void draw();
	virtual void moveCursor(float x, float y);

};

