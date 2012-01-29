#include "StdAfx.h"
#include "DeveloperConsole.h"
#include <D3DX10.h>

static GameSprite		consoleBackground;
static ID3DX10Font*		consoleFont;
	
list<wstring>	DeveloperConsole::messageList;
wstring			DeveloperConsole::currentMessage;

bool			DeveloperConsole::drawStats = false;
bool			DeveloperConsole::visible = false;
bool			DeveloperConsole::focused = DeveloperConsole::visible;
int				DeveloperConsole::lowerBound = 0;
TEXTMETRICW		DeveloperConsole::textInfo;

wstring			DeveloperConsole::currentCommand;
int				DeveloperConsole::currentCommandIndex = 0;
deque<wstring>	DeveloperConsole::commandList;
unsigned int	DeveloperConsole::cursorPosition = 0;

DeveloperConsole::DeveloperConsole(void)
{
}


DeveloperConsole::~DeveloperConsole(void)
{
}

void DeveloperConsole::init()
{	
	// Set up console.
	Utility::spriteFactory(&consoleBackground, L"consolebg.png");
	
	resize(Stats::getResolution());
	
	consoleBackground.position.x = 0;
	consoleBackground.position.z = ZOrdering::DeveloperConsole;
	consoleBackground.position.y = 0;

	messageList = list<wstring>();
	writeLine("Press ~ to toggle console visibility");
	writeLine("Press F2 to toggle console input catching");
	writeLine("Escape ends program, space full screens");
}

/*
 * Writes a line to the console (pushes at back)
 * Console lines are kept in a list, the front element being removed if the size exceeds MAX_MESSAGE_COUNT
 */
void DeveloperConsole::writeLine(string message)
{
	write(message);
	writeLine();	
}

void DeveloperConsole::writeLine(int i)
{
	write(i);
	writeLine();
}

void DeveloperConsole::writeLine()
{	
	messageList.push_back(currentMessage);
	currentMessage = L"";
	if(messageList.size() > MAX_MESSAGE_COUNT)
	{
		messageList.pop_front();
	}
}

void DeveloperConsole::write(string message)
{
	wstring messageWide = Utility::widen(message);
	if(messageWide.length() + currentMessage.length() < 2048)
		currentMessage.append(messageWide);
}

void DeveloperConsole::write(int i)
{
	char temp[255];
	string integ = itoa(i, temp, 10);
	write(integ);
}

// Called when the size of the screen is being redrawn.
void DeveloperConsole::resize(POINT size)
{
	consoleBackground.scale.x = (float)size.x;
	consoleBackground.scale.y = (float)size.y * SCREEN_PORTION;
	lowerBound = (int)(size.y * SCREEN_PORTION);

	// Following line restricts text height to MIN_TEXT_HEIGHT, otherwise it's sized based on the console height and maximum display allowance.
	int textHeight = (textHeight = lowerBound / (float)(1 + MAX_DISPLAY_COUNT)) < MIN_TEXT_HEIGHT ? MIN_TEXT_HEIGHT : textHeight;
	Utility::fontFactory((int)textHeight, L"Consolas", &consoleFont);

	// Make stuff transparent!
	consoleFont->DrawTextA(0, " ", -1, LPRECT(), DT_NOCLIP, D3DXCOLOR(1,1,1,1));

	consoleFont->GetTextMetricsW(&textInfo);
}

/*
 * Turns the console on/off
 * Toggles drawing, and forces focus into the same state.
 */
void DeveloperConsole::toggleVisible()
{
	visible = !visible;
	focused = visible;
}

// Returns whether the console is currently drawing.
bool DeveloperConsole::isVisible()
{
	return visible;
}

// Toggles whether the console is currently accepting input. Does nothing if not visible.
void DeveloperConsole::toggleFocus()
{
	focused = !focused;
	focused = focused && visible;
}

void DeveloperConsole::toggleDrawStats()
{
	drawStats = !drawStats;
}

// Returns whether the console is currently accepting input.
bool DeveloperConsole::hasFocus()
{
	return focused;
}

// Catches character input and puts it onto the current command.
void DeveloperConsole::catchCharacter(wchar_t c)
{
	if(focused)
	switch(c)
	{
		
		// Invalid characters.
		case L'`':
		case L'~':
		// Unicode for backspace
		case 8: 
		// Carraige return characters that I could find.
		case 0x23CE:
		case 0x240D:
		case 0x0D:
			break;		
		default:
			if(currentCommand.length() < 255)
			{
				currentCommand.insert(cursorPosition, &c);
				setCursor(cursorPosition + 1);
			}
	}
}

// Attempts to set the cursor to the specific index. Restricts it to 0 and the end of the list.
void DeveloperConsole::setCursor(int index)
{
	if(index < 0)
		index = 0;
	if(index > currentCommand.length())
		index = currentCommand.length();
	cursorPosition = index;
}

// Attempts to select a command. Restrics to within the command list.
void DeveloperConsole::selectCommand(int index)
{
	if(commandList.size() > 0)
	{
		if(index >= commandList.size())
			index = 0;
		if(index < 0)
			index = commandList.size() - 1;
		currentCommand = commandList[index];
		currentCommandIndex = index;
		setCursor(cursorPosition);
	}
}

// Takes the current command and pushes it to the list.
// Does not accept empty strings.
void DeveloperConsole::pushCurrentCommand()
{
	if(currentCommand != L"")
	{		
		Utility::parseCommand(Utility::narrow(currentCommand));

		if(commandList.size() > 0)
			commandList.pop_front();				// Remove old empty end string
		commandList.push_front(currentCommand);		// Add previous command.
		commandList.push_front(L"");				// Readd command.

		if(commandList.size() > MAX_COMMANDLIST_SIZE)
		{
			commandList.pop_back();
		}
		setCursor(0);
		selectCommand(0);
	}
}

// Catches key input.
// Currently only catches:
//	~	Toggles active
//	F2	Toggles visible (will work when I merge my code from home)
bool DeveloperConsole::catchKey(KeyState key)
{
	switch(key.keyCode)
	{
		case KeyCodes::F2:
			toggleFocus();		return true;
		case KeyCodes::Tilde:
			toggleVisible();	return true;
		case KeyCodes::F8:
			toggleDrawStats();	return true;
	}
	if(hasFocus())
	{
		switch(key.keyCode)
		{
			case KeyCodes::ENTER:
				pushCurrentCommand();
				break;
			case KeyCodes::BACKSPACE:
				if(cursorPosition > 0)
				{
					currentCommand.erase(cursorPosition - 1, 1);
					setCursor(cursorPosition - 1);
				}
				break;
			case KeyCodes::DELETE_B:
				if(cursorPosition < currentCommand.length())
				{
					currentCommand.erase(cursorPosition, 1);
					setCursor(cursorPosition);
				}
				break;
			case KeyCodes::UP:
				selectCommand(currentCommandIndex + 1);
				break;
			case KeyCodes::DOWN:
				selectCommand(currentCommandIndex - 1);
				break;
			case KeyCodes::LEFT:
				setCursor(cursorPosition - 1);
				break;
			case KeyCodes::RIGHT:
				setCursor(cursorPosition + 1);
				break;
				
		}
		return true;
	}
	return false;
}

/*
 * Draws the console and the lines.
 * Draws a blank line (later to have user input) at the bottom line, and draws MAX_DISPLAY messages above it.
 */
void DeveloperConsole::drawConsole()
{

	if(visible)
	{
		addToDrawAbs(consoleBackground);
		RECT r;
		int m_count = MAX_DISPLAY_COUNT - 2;
		r.left = 0;
		r.right = 1;
		r.top = lowerBound - (int)textInfo.tmHeight;

		// Draw the current command. 
		consoleFont->DrawTextW(0, currentCommand.c_str(), -1, &r, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(1,1,1,1));
		
		// Draw the cursor.
		r.left = textInfo.tmAveCharWidth * cursorPosition;
		consoleFont->DrawTextW(0, L"_", -1, &r, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(1,1,1,1));
		
		r.left = 0;
		r.top -= textInfo.tmHeight;

		// Draw the working line.
		r.top -= consoleFont->DrawTextW(0, currentMessage.c_str(), -1, &r, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(1,1,1,1));

		// Draws from the bottom up. Uses reverse iterator since newest messages are at the back of the list.
		for(list<wstring>::reverse_iterator it = messageList.rbegin(); it != messageList.rend() && m_count >= 0; it++)
		{
			r.top -= consoleFont->DrawTextW(0, (*it).c_str(), -1, &r, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(1,1,1,1));//THIS LINE. THIS ONE. RIGHT HERE. Something here is why it changes from solid to transparent
			m_count--;
		}
	}
	if(drawStats)
	{
		char temp[64];
		string statsString = "";
		RECT r;
		r.left = 0;
		r.top = 0;
		r.right = Stats::getScreenSize().x;
		r.bottom = Stats::getScreenSize().y;
		
		statsString.append("FPS: ");
		itoa(Stats::getFPS(), temp, 10);
		statsString.append(temp);
		statsString.append("\n");

		statsString.append("dt: ");
		itoa(Stats::dt()*1000, temp, 10);
		statsString.append(temp);
		statsString.append("ms\n");
		consoleFont->DrawTextA(0, statsString.c_str(), -1, &r, DT_NOCLIP | DT_RIGHT | DT_TOP, D3DXCOLOR(1, 1, 1, 1));
	}
}