#pragma once
#include "WindowsInputMapping.h"

// Interperts a windows message into slightly more usable key information.
// See http://msdn.microsoft.com/en-us/library/ms646280(v=vs.85).aspx
// Not done.
class KeyState
{
//------------------------ Members -------------------------------------
public:
	unsigned int	keyCode;		// The VK_CODE for the key. See; http://msdn.microsoft.com/en-us/library/dd375731(v=vs.85).aspx
	unsigned int	autoRepeat;		// Number of times the key was autorepeated due to holding the key
	bool			justPressed;	// Whether the key was down previously. Possibly derivable from autorepeat being non-zero.
	
	// Modifier keys
	static bool		shiftDown;
//------------------------ Methods -------------------------------------
public:
	KeyState(WPARAM wparam, LPARAM lparam);
	~KeyState(void);
};

