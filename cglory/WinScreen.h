#pragma once
#include "InputCatcher.h"
class WinScreen :
	public InputCatcher
{
public:
	WinScreen(void);
	~WinScreen(void);

	void draw();
	void gainFocus();
	bool catchKey(KeyState k);
};

