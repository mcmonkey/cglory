#pragma once
#include "attackcursor.h"

class BombardCursor :
	public AttackCursor
{
public:
	virtual void select();
	BombardCursor(Unit* u);
	~BombardCursor(void);
};

