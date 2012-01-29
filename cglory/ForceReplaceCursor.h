#pragma once
#include "GameCursor.h"
class ForceReplaceCursor : public GameCursor
{
public:
	GameObject* placing;

public:

	void draw();
	void select();
	bool catchKey(KeyState);

	ForceReplaceCursor(GameObject* g);
	~ForceReplaceCursor(void);
};

