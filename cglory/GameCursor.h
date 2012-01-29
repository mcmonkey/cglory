#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include "UIElement.h"


using namespace std;

class GameCursor : public UIElement
{
public:

	GameSprite userCursor;
	GameSprite selectedOverlay;

	POINT tilePos;

	GameCursor(void);
	~GameCursor(void);

	virtual void moveCursor(float x, float y);

	void moveCursorAbs(float x, float y);
	void calcTilePos();
	void setOverlayPos();
	void checkForScrolling();
	
	
	
	// InputCatcher Methods
	virtual bool catchKey(KeyState);
	virtual void gainFocus();

	//UIElement Methods
	virtual void generalInit();
	virtual void draw();
	virtual void select();
	
	

};

