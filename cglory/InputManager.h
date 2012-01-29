#pragma once
#include <list>
#include "InputCatcher.h"
#include <typeinfo>
#include "GameCursor.h"
#include "InfoTab.h"

using namespace std;
// Recieves keyboard event information from the operating system, parsed as KeyStates (see:KeyState)
class InputManager
{
//------------------------ Members -------------------------------------
private:
	static  vector<InputCatcher*> catchers;	// Stack of InputCatchers. Input is given to the back first, then down.
public:
	static  GameCursor*			  mainCursor;  

//------------------------ Methods -------------------------------------
public:
	static void registerCatcher(InputCatcher * ic);
	static void removeCatcher();
	static void clearCatchers();
	static void keyDown(KeyState key);
	static void textInput(wchar_t t);
	static void init();
	InputManager(void);
	~InputManager(void);

	static void drawAll();

};

