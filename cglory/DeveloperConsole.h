#pragma once
#include <list>
#include <string>
#include "Utility.h"
#include "KeyState.h"
#include <deque>

// Logical Units = lu = pixels for all practical purposes.
// If it says pixels though, it's in pixels.

const float			SCREEN_PORTION		= .35f; // Vertical porition of the screen covered by the console.
const unsigned int	MIN_TEXT_HEIGHT		= 20;	// Minimum height of text in the console in lu
const int			MAX_COMMANDLIST_SIZE= 10;	// Maximum number of commands that will be stored in history

/* Class to display textual console output, and to accept input at some point.
 * Oldest messages are stored at the front end of the list.
 */
class DeveloperConsole
{

//------------------------ Constants -------------------------------------
private:
	static const int	MAX_DISPLAY_COUNT	= 10;		// Maximum number of messages that will be displayed in the queue.	
public:
	static const int	MAX_MESSAGE_COUNT	= 10;		// Maximum number of messages that will be stored.

//------------------------ Members -------------------------------------
private:
	static list<wstring>	messageList;	// List of string being displayed in the console.
	static wstring			currentMessage;	// Current message, used in write function

	static bool				visible;	// Is the console visible?
	static bool				focused;	// Is the console accepting input?
	static bool				drawStats;	// Drawing the fps (and maybe more!)

	static int				lowerBound;	// Bottom of the console in pixels.
	static TEXTMETRICW		textInfo;	// Text metrics info, like actual height and width
	
	static wstring			currentCommand;		// The current string being typed in to the console.
	static int				currentCommandIndex;// The index in deque of the currently selected command.
	static deque<wstring>	commandList;		// List of past commands (includes the most recent).
	static unsigned int		cursorPosition;		// Where the cursor currently is in the current command. WARNING: Don't manually set, use setCursor

//------------------------ Methods -------------------------------------
public:
	DeveloperConsole(void);
	~DeveloperConsole(void);
	static void init();
	static void writeLine(string message);
	static void writeLine(int i);
	static void writeLine();
	static void write(string message);
	static void write(int i);
	static void resize(POINT size);
	static void drawConsole();
	static void toggleVisible();
	static void toggleFocus();
	static bool isVisible();
	static bool hasFocus();
	static void catchCharacter(wchar_t c);
	static bool catchKey(KeyState key);

private:
	static void selectCommand(int i);
	static void pushCurrentCommand();
	static void setCursor(int i);
	static void toggleDrawStats();
};

