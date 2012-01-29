#pragma once
#include "GameCursor.h"
#include "Unit.h"
#include "CellPathNode.h"
#include "Map.h"



class AttackCursor: public GameCursor
{
public:
	AttackCursor(void);
	~AttackCursor(void);
	AttackCursor(Unit* u);


	Unit* unit;
	GameSprite available;

	vector<shared_ptr<CellPathNode>> cPN;

	void generalInit();
	void select();
	void draw();
	virtual bool catchKey(KeyState);
};

