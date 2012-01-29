#include "StdAfx.h"
#include "UIMenu.h"
#include "PlayManager.h"
#include "InputManager.h"
#include "Sound.h"

UIMenu::UIMenu(void)
{
	gObj = 0x0;
	currCell = NULL;

	generalInit();
	
	setupSprites();

}

UIMenu::UIMenu(GameObject* g)
{
	gObj = g;
	currCell = NULL;
	if(g)
		currCell = g->getCell();
	if(currCell)
		prevLoc = currCell->position;
}

UIMenu::UIMenu(Cell* c)
{
	currCell = c;
	prevLoc = currCell->position;
	gObj = 0;
}

UIMenu::~UIMenu(void)
{

}

void UIMenu::generalInit()
{
	//construct the font object
	menuOptionHeight = 20;

	//set up the cursor for the menu like we did for pretty much every other gameSprite
	int tileSize = Stats::getTilesize();
	Utility::spriteFactory(&mCursor, L"menuCursor.png");
	mCursor.hasAnimation = true;
	mCursor.position = D3DXVECTOR3(0.0f*tileSize, 0.0f*tileSize, 10);
	mCursor.texCoord.x = 1.0f/(mCursor.originalSize.x/tileSize) * 1;
	mCursor.texCoord.y = (1.0f/(mCursor.originalSize.y/tileSize)-1) * 1;
	mCursor.drawSize = D3DXVECTOR2((float)menuOptionHeight, (float)menuOptionHeight);
	mCursor.sprite->TexSize.x = 1.0f/(mCursor.originalSize.x/tileSize);
	mCursor.sprite->TexSize.y = 1.0f/(mCursor.originalSize.y/tileSize);
	//mCursor.scale.x = 20.0/32.0;
	//mCursor.scale.y = 20.0/32.0;

	mCursor.position.z = ZOrdering::DeveloperConsole;

	//set these to 0 to start
	optionSelection = 0;
	options = 0;

	//load the bg for the menu
	Utility::spriteFactory(&bg, L"consolebg.png");
	bg.position.z = ZOrdering::DeveloperConsole;
	//set the width. The length is determined by the amount of options
	bg.scale.x = 100;

	//setup a sprite that will show where the cursor was, but without the cursor
	Utility::spriteFactory(&selected, L"selected.png");
	selected.position = D3DXVECTOR3(prevLoc.x, prevLoc.y, ZOrdering::MapOverlay);
	
	

	//make sure this is added to the manager
	InputManager::registerCatcher(this);
}



void UIMenu::gainFocus()
{
	
	clearOptions();
	setupOptions();
	setupMenuDrawspace();
}

void UIMenu::setupOptions()
{
	addOption(L"Exit", -1);
}

void UIMenu::clearOptions()
{
	optionNames.clear();
	selectable.clear();
	options = 0;
}

void UIMenu::addOption(wstring name, int id)
{
	addOption(name, id, true);
}

void UIMenu::addOption(wstring name, int id, bool isSelectable)
{
	optionNames.push_back(name);
	selectable.push_back(isSelectable);
	optionIds[name] = id;
	options++;
}

int UIMenu::selectedId()
{
	return optionIds[optionNames[optionSelection]];
}
void UIMenu::setupMenuDrawspace()
{
	if(gObj)
		currCell = gObj->getCell();

	//setup the space for the text drawing
	//the size of the overlay should encompass all of the options
	bg.scale.y = menuOptionHeight*options;
	//if we have a gameobject, then draw based on that
	if(currCell)
	{
		drawSpace.left		= (long)(currCell->position.x +16 /*- Utility::camera->x*/);
		drawSpace.right		= (long)(drawSpace.left + bg.scale.x);
		drawSpace.top		= (long)(currCell->position.y +16 /*- Utility::camera->y*/);
		drawSpace.bottom	= (long)(drawSpace.top + bg.scale.y);
	}
	else
	{
		//otherwise, draw like this
		
		drawSpace.left = 0;
		drawSpace.right = drawSpace.left + bg.scale.x;
		drawSpace.top = 0;
		drawSpace.bottom = drawSpace.top + bg.scale.y;
	}

	//do a check to make sure that the drawspace isn't going beyond the view of the player
	if(drawSpace.top + menuOptionHeight*options > Stats::getScreenSize().y + Utility::camera->y)
	{
		//if we're here, then the menu is too low
		//figure out the difference and push it up
		long diff = (drawSpace.top + menuOptionHeight*options) - (Stats::getScreenSize().y + Utility::camera->y);
		drawSpace.top-=diff;
		drawSpace.bottom-=diff;
	}
	if(drawSpace.right > Stats::getScreenSize().x + Utility::camera->x)
	{
		long diff = (drawSpace.right) - (Stats::getScreenSize().x + Utility::camera->x);
		drawSpace.left -= diff;
		drawSpace.right -= diff;
	}
}

void UIMenu::setupSprites()
{
	//let the positions of the bg and the cursor based on the drawSpace
	bg.position.x = drawSpace.left /*+Utility::camera->x*/;
	bg.position.y = drawSpace.top /*+Utility::camera->y*/;
	mCursor.position.x = drawSpace.left - menuOptionHeight /*+Utility::camera->x*/;
	mCursor.position.y = drawSpace.top/* +Utility::camera->y*/;
}

void UIMenu::moveSelection(int x, int y)
{

	//move the optionSelection in the direction of the y
	optionSelection += y;
	if(optionSelection < 0 || optionSelection >=options)
	{
		//to get optionSelection within the correct bounds, we can add to it the product of the number of options time the opposite of optionSelection's sign
		optionSelection += options*optionSelection/ fabs((double)optionSelection)*-1;
	}
	//then change the mCursor's position to match accordingly
	mCursor.position.y = (optionSelection*menuOptionHeight) + drawSpace.top;
}

void UIMenu::select()
{
	select(selectedId());
}

void UIMenu::select(int selectedId)
{
	//default is to just pop
	if(selectedId == -1)
		InputManager::removeCatcher();
}

void UIMenu::draw()
{
	//make sure we're drawing at the right spot. the gSprite may have moved
	//so check to see if it has moved
	if(currCell && (prevLoc.y != (currCell->position.y) || prevLoc.x	!= (currCell->position.x)))
	{
		//if it has moved, redo the setup
		setupMenuDrawspace();
		setupSprites();
		moveSelection(0,0);
		//and set prevLoc
		prevLoc.y = (currCell->position.y);
		prevLoc.x = (currCell->position.x);
		//and update the selected sprite
		selected.position = D3DXVECTOR3(prevLoc.x, prevLoc.y, ZOrdering::MapOverlay);
	}

	//add the background and the cursor to draw
	addToDraw(selected);
	addToDraw(bg);
	addToDraw(mCursor);
	

	//then, for each optionName, we should draw text for it
	RECT tempDrawSpace = drawSpace;
	//since text draws by absolute, subtract the camera from the tempDrawSpace
	tempDrawSpace.top -= Utility::camera->y;
	tempDrawSpace.left -= Utility::camera->x;
	D3DXCOLOR color;
	for(int i=0; i<optionNames.size(); i++)
	{
		color = selectable[i] ? D3DXCOLOR(1, 1, 1, 1) : D3DXCOLOR(.5, .5, .5, 1);
		tempDrawSpace.top += FontManager::menuFont->DrawTextW(0, optionNames.at(i).c_str(), -1, &tempDrawSpace, DT_NOCLIP | DT_SINGLELINE, color);
	}
	
}

bool UIMenu::catchKey(KeyState key)
{
	//overriding InputCatcher::catchKey to serve functionality here
	switch(key.keyCode)
	{
		case KeyCodes::DOWN:
			moveSelection(0,  1); return true;
		case KeyCodes::UP:
			moveSelection(0, -1); return true;
		case KeyCodes::LEFT:
			return true;
		case KeyCodes::RIGHT:
			return true;
		case KeyCodes::ENTER:
			selectable[optionSelection] ? select() : 0/*play annoying sound*/ ;	   return true;
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
	}
	return false;
}