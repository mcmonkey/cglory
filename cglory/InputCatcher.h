#pragma once
#include "KeyState.h"

class InputCatcher
{
//------------------------ Methods -------------------------------------
public:
	virtual bool catchKey(KeyState key) = 0;
	virtual void draw() = 0;
	virtual void gainFocus() = 0;
};