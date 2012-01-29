#pragma once
#include "InputCatcher.h"
#include "Unit.h"

class AmbushDirectionSelector : public InputCatcher
{
private:
	vector<Cell*>	ambushable;
	Unit*			ambusher;

public:
	bool catchKey(KeyState k);
	void gainFocus();
	void draw();
	AmbushDirectionSelector(Unit*);
	~AmbushDirectionSelector(void);
};

