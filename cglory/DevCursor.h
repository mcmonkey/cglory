#pragma once
#include "GameCursor.h"

class DevCursor : public GameCursor
{
public:
	DevCursor(void);
	~DevCursor(void);

	//void generalInit();
	void select();
	void draw();
	virtual bool catchKey(KeyState);
};

