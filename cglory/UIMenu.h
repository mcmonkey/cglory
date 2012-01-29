#pragma once
#include "UIMenu.h"
#include "UIElement.h"
#include "InputCatcher.h"
#include "GameSprite.h"
#include "GameObject.h"
#include "Cell.h"
#include <map>

class UIMenu : public UIElement
{
public:
	UIMenu(void);
	UIMenu(GameObject* g);
	UIMenu(Cell* c);
	~UIMenu(void);

	GameSprite mCursor;
	GameSprite bg;
	GameSprite selected;

	RECT drawSpace;

	GameObject* gObj;

	int options;
	int optionSelection;
	vector<wstring>		optionNames;
	map<wstring, int>	optionIds;
	vector<bool>		selectable;

	float menuOptionHeight;

	D3DXVECTOR3 prevLoc;
	Cell* currCell;
	
	void addOption(wstring name, int id);
	void addOption(wstring name, int id, bool selectable);

	inline int	 selectedId();

	virtual void setupOptions();
	virtual void clearOptions();

	virtual void generalInit();
	virtual void setupMenuDrawspace();
	virtual void setupSprites();
	virtual void moveSelection(int x, int y);
	
	void select();
	virtual void select(int selectedId);

	virtual void draw();
	// InputCatcher Methods
	virtual bool catchKey(KeyState);
	virtual void gainFocus();
	
};