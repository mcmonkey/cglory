#pragma once
#include "ActionMenu.h"
#include <deque>

using namespace std;

class ActionMenu;

class MenuManager
{
public:
	//-------Members-----------//
	static deque<ActionMenu*> menus;

	//-------Methods----------//
	static void draw();
	static void addMenu(ActionMenu* aM);
	static void removeMenu();

	MenuManager(void);
	~MenuManager(void);
};

