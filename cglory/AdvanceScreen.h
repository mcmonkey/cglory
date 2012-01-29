#pragma once
#include <string>
#include "uielement.h"

class AdvanceScreen :
	public UIElement
{
private:
	string message;

public:
	AdvanceScreen(void);
	~AdvanceScreen(void);

	GameSprite bg;
	ID3DX10Font* consoleFont;
	RECT drawSpace;

	virtual void select();
	virtual void generalInit();
	virtual void draw();
	virtual void gainFocus();

	// InputCatcher Methods
	virtual bool catchKey(KeyState);
};

