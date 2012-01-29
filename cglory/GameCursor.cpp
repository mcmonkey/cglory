#include "StdAfx.h"
#include "GameCursor.h"
#include <vector>
#include "InputManager.h"
#include "PlayManager.h"
#include "Cell.h"
#include "Stats.h"
#include "CardMenu.h"


GameCursor::GameCursor(void)
{
	generalInit();
}


GameCursor::~GameCursor(void)
{
}

void GameCursor::generalInit()
{
	//load in the sprite and set all its variables similar to how we deal with bgTiles in dxManager
	int tileSize = Stats::getTilesize();

	Utility::spriteFactory(&userCursor, L"cursorAnimation.png");
	userCursor.hasAnimation = true;
	userCursor.position = D3DXVECTOR3(0.0f*tileSize, -0.5f*tileSize, 10);
	userCursor.texCoord.x = 1.0f/(userCursor.originalSize.x/tileSize) * 1;
	userCursor.texCoord.y = (1.0f/(userCursor.originalSize.y/tileSize)-1) * 1;
	userCursor.drawSize = D3DXVECTOR2((float)tileSize, (float)tileSize);
	userCursor.sprite->TexSize.x = 1.0f/(userCursor.originalSize.x/tileSize);
	userCursor.sprite->TexSize.y = 1.0f/(userCursor.originalSize.y/tileSize);

	userCursor.position.z = ZOrdering::Building;

	Utility::spriteFactory(&selectedOverlay, L"selected.png");

	selectedOverlay.position.z = ZOrdering::MapSelector;

	calcTilePos();
	InputManager::registerCatcher(this);
}

bool GameCursor::catchKey(KeyState key)
{
	switch(key.keyCode)
	{
		case KeyCodes::DOWN:
			moveCursor(0,  1); return true;
		case KeyCodes::UP:
			moveCursor(0, -1); return true;
		case KeyCodes::LEFT:
			moveCursor(-1, 0); return true;
		case KeyCodes::RIGHT:
			moveCursor( 1, 0); return true;
		case KeyCodes::ENTER:
			select();		   return true;
		case KeyCodes::CTRL:
			new CardMenu(PlayManager::getCurrentMap()->getCell(InputManager::mainCursor->tilePos.x,InputManager::mainCursor->tilePos.y)); return true;
	}
	return false;
}

void GameCursor::moveCursor(float x, float y)
{
	//the values passed in determine in what direction. they should be [-1,1]
	userCursor.position.x += (float)Stats::getTilesize() * x;
	userCursor.position.y += (float)Stats::getTilesize() * y;
	//prevent it from going too far
	if(userCursor.position.x < 0) userCursor.position.x = 0;
	if(userCursor.position.x >= (float)Stats::getMapsize().x) userCursor.position.x = Stats::getMapsize().x - (float)Stats::getTilesize();
	if(userCursor.position.y < -(float)Stats::getTilesize()/2) userCursor.position.y = -(float)Stats::getTilesize()/2;
	if(userCursor.position.y >= (float)Stats::getMapsize().y - (float)Stats::getTilesize()*1.5f) userCursor.position.y = Stats::getMapsize().y - (float)Stats::getTilesize()*1.5f;

	//figure out over what tile we are
	calcTilePos();
	//set the position of the selectedOverlay
	setOverlayPos();
	//and then check to see if we need to move the screen to keep our cursor visible at all
	checkForScrolling();
	
	PlayManager::info->updateWithReferenceTo(PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y));
	
}

void GameCursor::moveCursorAbs(float x, float y)
{
	//set to the origin and then translate using the function we have
	userCursor.position.x = 0;
	userCursor.position.y = -16;
	//now translate
	moveCursor(x, y);
}

void GameCursor::calcTilePos()
{
	//the tilePos is where the cursor lies in terms of tiles
	tilePos.x = floor((userCursor.position.x + Stats::getTilesize()/2) / Stats::getTilesize());
	tilePos.y = floor((userCursor.position.y + userCursor.originalSize.y/2) / Stats::getTilesize());
}

void GameCursor::setOverlayPos()
{
	//use the tilePos to determine where to place the selected
	selectedOverlay.position.x = tilePos.x * Stats::getTilesize();
	selectedOverlay.position.y = tilePos.y * Stats::getTilesize();
}

void GameCursor::checkForScrolling()
{
	//the edges of the screen are the active area for scrolling. The edge will be probably 1/4 the size of the tile
	//if the cursur is within them and not at the edge of the map itself, scroll the screen

	//get bools determining which way we need to scroll.
	bool scrollLeft = (userCursor.position.x - Utility::camera->x < Stats::getTilesize()/4);
	bool scrollRight = (userCursor.position.x - Utility::camera->x > (Stats::getScreenSize().x - Stats::getTilesize()/4));
	bool scrollUp = (userCursor.position.y - Utility::camera->y < Stats::getTilesize()/4);
	bool scrollDown = (userCursor.position.y - Utility::camera->y > (Stats::getScreenSize().y - Stats::getTilesize()/4));

	POINT p = Stats::getScreenSize();
	float f = (float)Stats::getTilesize()/4;

	//get bools on if we are allowed to move
	bool canLeft = Utility::camera->x > 0;
	bool canRight = Utility::camera->x + Stats::getScreenSize().x  < Stats::getMapsize().x;
	bool canUp = Utility::camera->y > 0;
	bool canDown = Utility::camera->y + Stats::getScreenSize().y < Stats::getMapsize().y;

	POINT q = Stats::getMapsize();

	if(scrollLeft && canLeft)
	{
		Utility::moveCamera(-(float)Stats::getTilesize(),0);
	}
	else if(scrollRight && canRight)
	{
		Utility::moveCamera((float)Stats::getTilesize(),0);
	}
	
	if(scrollUp && canUp)
	{
		Utility::moveCamera(0,-(float)Stats::getTilesize());
	}
	else if(scrollDown && canDown)
	{
		Utility::moveCamera(0,(float)Stats::getTilesize());
	}

}

void GameCursor::gainFocus()
{
	
}

void GameCursor::select()
{
	//based on the position, visibility and contents of a cell, call the select of a visible GameObject. 
	//use a loop to from the top layer down using CellLayers::Count
	Cell* selectedCell = PlayManager::getCurrentMap()->getCell(tilePos.x, tilePos.y);

	for(int i = CellLayers::Count - 1; i >=0; i-- )
	{
		GameObject* g = selectedCell->objectAtLayer(i);
		if(g && g->visibleTo(*PlayManager::getActivePlayer()))
		{
			g->select();
			break;
		}
	}
	
}

void GameCursor::draw()
{
	//add the overlay and the cursor to the draw
	addToDraw(selectedOverlay);
	addToDraw(userCursor);
}