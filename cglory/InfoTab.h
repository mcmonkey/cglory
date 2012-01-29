#pragma once
#include "InputCatcher.h"
#include "Cell.h"
class InfoTab :
	public InputCatcher
{
public:
	InfoTab(void);
	~InfoTab(void);

	bool isRobust;

	vector<string> currentInfo;

	GameSprite bg;
	GameSprite glorybg;
	ID3DX10Font* font;
	RECT drawspace;
	RECT gloryDrawspace;
	Cell* currCell;
	int currLayer;
	bool drawBottom;
	bool drawRight;


	void setupDrawspace();
	void setupBgSize();
	void setupBgPos();
	void offsetDrawspace();
	void reevaluate();
	void updateWithReferenceTo(Cell* c);
	void cycleToNext();
	void getInfo();
	void updateWithCardInfo(vector<string> info, bool robust);

	void checkResize();

	void toggleRobust();

	//input catcher methods
	virtual bool catchKey(KeyState key);
	virtual void draw();
	virtual void gainFocus();
};

