#pragma once
#include "InputCatcher.h"

// Abstract class for halting input while an animation takes place.
class AnimationStop : public InputCatcher
{
protected:
	bool ready;

public:
	virtual bool isReady();
	virtual bool catchKey(KeyState k);

	virtual void draw() = 0;
	virtual void update() = 0;
	
	virtual void gainFocus();

	AnimationStop(void);
	~AnimationStop(void);
};

