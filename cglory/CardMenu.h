#pragma once
#include "UIMenu.h"
class CardMenu : public UIMenu
{
public:
	CardMenu(void);
	CardMenu(Cell *c);
	~CardMenu(void);

	vector<GameSprite> cards;
	bool sendRobust;

	void drawHand();
	void setupCards();
	void updateInfoTab(bool robust);

	virtual void setupOptions();
	virtual void select(int selectedId);
	virtual void generalInit();

	virtual void draw();
	virtual void moveSelection(int x, int y);
	virtual bool catchKey(KeyState);

	virtual void gainFocus();
};

