#pragma once
#include "GameSprite.h"
#include "InputCatcher.h"
#include <math.h>
#include "MenuManager.h"
#include "SelectionCursor.h"
#include "AttackCursor.h"


class ActionMenu : public InputCatcher
{
public:
	ActionMenu(void);
	ActionMenu(Unit* u);
	ActionMenu(Building* b);
	ActionMenu(int mType, void* p);
	~ActionMenu(void);

	int menuType;

	GameSprite mCursor;
	GameSprite bg;
	GameSprite available;

	ID3DX10Font* consoleFont;
	RECT drawSpace;

	Unit* unit;
	Building* build;

	int options;
	int optionSelection;
	vector<wstring> optionNames;
	float menuOptionHeight;

	void select();
	void moveSelection(int x, int y);
	void generalInit();
	void draw();

	// InputCatcher Methods
	bool catchKey(KeyState);
};

