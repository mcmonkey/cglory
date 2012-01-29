#pragma once
#include "uimenu.h"
class TitleMenu :
	public UIMenu
{
public:
	wstring title;

	virtual void setupMenuDrawspace();
	virtual void setupSprites();
	virtual void draw();
	
	virtual void setupOptions();
	virtual void select(int id);

	virtual bool catchKey(KeyState k);

	TitleMenu(void);
	~TitleMenu(void);
};

