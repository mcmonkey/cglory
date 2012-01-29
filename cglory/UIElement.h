#pragma once
#include "GameSprite.h"
#include "InputCatcher.h"
//
class UIElement : public InputCatcher
{
public:
	virtual void generalInit()=0;
	virtual void draw()=0;

	// InputCatcher Methods
	virtual bool catchKey(KeyState)=0;
};

