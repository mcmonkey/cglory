#include "stdafx.h"
#include "InputManager.h"
#include "PlayManager.h"
#include <algorithm>

vector<InputCatcher*> InputManager::catchers;
GameCursor* InputManager::mainCursor;

void InputManager::init()
{
	
}

void InputManager::registerCatcher(InputCatcher * ic)
{
	if(ic)
	{
		auto i = catchers.begin();
		if((i = find(i, catchers.end(), ic)) != catchers.end())
			catchers.erase(i);

		catchers.push_back(ic);
		ic->gainFocus();
		
	}
	
}

void InputManager::removeCatcher()
{
	delete catchers.back();
	catchers.pop_back();
	if(catchers.size() > 0)
	{
		catchers.back()->gainFocus();
	}
}

void InputManager::clearCatchers()
{
	while(catchers.size() > 0)
		removeCatcher();
}

void InputManager::keyDown(KeyState key)
{
	// Dev console gets perma-first dibs.
	if(DeveloperConsole::catchKey(key)){}
	else
		// Otherwise it's last come, first serve.
		for(vector<InputCatcher*>::reverse_iterator it = catchers.rbegin(); it < catchers.rend(); it++)
		{
			if((*it)->catchKey(key)) break;
		}
	return;
	
}

void InputManager::textInput(wchar_t t)
{

}

void InputManager::drawAll()
{
	/*for(vector<InputCatcher*>::reverse_iterator it = catchers.rbegin(); it < catchers.rend(); it++)
		{
			(*it)->draw();
		}*/
	//only draws the last menu to be added
	if(catchers.size() > 0)
		catchers[catchers.size()-1]->draw();
}
InputManager::InputManager(void)
{
}

InputManager::~InputManager(void)
{
}
