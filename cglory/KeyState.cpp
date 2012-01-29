#include "StdAfx.h"
#include "KeyState.h"


KeyState::KeyState(WPARAM wparam, LPARAM lparam )
{
	autoRepeat = 0xFFFF & lparam; // first 16 bits of the lparam.
	keyCode = wparam;
	justPressed = !((0x1 << 0x1E) & lparam); // bit 30 of the lparam is 1 if key was down, 0 elsewise
}


KeyState::~KeyState(void)
{
}
