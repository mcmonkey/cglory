#include "StdAfx.h"
#include "MenuManager.h"

deque<ActionMenu*> MenuManager::menus;

MenuManager::MenuManager(void)
{
}


MenuManager::~MenuManager(void)
{
}

void MenuManager::addMenu(ActionMenu* aM)
{
	//push a menu into the list and register it as an input catcher
	menus.push_front(aM);
	InputManager::registerCatcher(aM);
}

void MenuManager::removeMenu()
{
	//remove a menu from the menu list and unregister it as an input catcher
	menus.pop_front();
	InputManager::removeCatcher();
}

void MenuManager::draw()
{
	//draw only the last menu to be added in
	//and only if there are actually menus in the list
	if(menus.size()>0)
		menus.at(0)->draw();

	/*for(int i = 0; i<menus.size(); i++)
	{
		menus.at(i)->draw();
	}*/
}