#include "StdAfx.h"
#include "InfoTab.h"
#include "Unit.h"
#include "Building.h"
#include "Terrain.h"
#include "PlayManager.h"
#include "FontManager.h"
#include "Utility.h"
#include "InputManager.h"


InfoTab::InfoTab(void)
{
	isRobust = false;
	currentInfo = vector<string>();
	font = FontManager::menuFont;
	Utility::spriteFactory(&bg, L"infotab.png");
	bg.drawSize = D3DXVECTOR2(1,1);
	Utility::spriteFactory(&glorybg, L"glorytab.png");
	glorybg.drawSize = D3DXVECTOR2(1,1);
	updateWithReferenceTo(PlayManager::getCurrentMap()->getCell(0,0));
	InputManager::registerCatcher(this);
}


InfoTab::~InfoTab(void)
{
}

void InfoTab::updateWithReferenceTo(Cell* c)
{
	isRobust = false;
	currCell = c;
	//first lets see if the player can see the space we're at
	//if he can't, then we can ignore units at this spot
	bool playerCanSee = currCell->visibleTo(*PlayManager::getActivePlayer());
	
	//start the iteration at 0 unless we can't see, then start it at 1 to skip units
	currLayer = CellLayers::Terrain;
	int layerPos = CellLayers::Count;
	if(!playerCanSee)
		layerPos--;

	//go through from where we start descending
	for(;layerPos > -1; layerPos--)
	{
		//if there exists an object at the layer
		if(currCell->objectAtLayer(layerPos) && currCell->objectAtLayer(layerPos)->visibleTo(*PlayManager::getActivePlayer()))
		{
			currLayer = layerPos;
			break;
		}
			
	}

	//update the drawSpace and background image
	reevaluate();


}

void InfoTab::updateWithCardInfo(vector<string> info, bool robust)
{
	currentInfo = info;
	isRobust = robust;
	setupBgSize();
	setupBgPos();
	setupDrawspace();
}

void InfoTab::getInfo()
{
	currentInfo.clear();

	if(currCell && currCell->objectAtLayer(currLayer))
	if(!isRobust)
	{
		currCell->objectAtLayer(currLayer)->giveInfo(&currentInfo);
	}
	else
	{
		currCell->objectAtLayer(currLayer)->giveRobustInfo(&currentInfo);
	}
}

void InfoTab::reevaluate()
{
	getInfo();
	setupBgSize();
	setupBgPos();
	setupDrawspace();
}

void InfoTab::toggleRobust()
{
	isRobust = !isRobust;
	reevaluate();
}

void InfoTab::cycleToNext()
{
	do
	{
		currLayer--;
		if(currLayer < 0)
		{
			isRobust = false;
			currLayer = CellLayers::Count;
			//just a tiiiiiiny hack right here since I can't figure a better way
			//when the cursor is on the top half, we're turning from being robust, and the infotab is on the right
			if(drawBottom && bg.position.x < Stats::getScreenSize().x/2)
				bg.position.x = 0;
		}
			
	}
	while(! (currCell->objectAtLayer(currLayer) && currCell->objectAtLayer(currLayer)->visibleTo(*PlayManager::getActivePlayer())));
	reevaluate();
}

void InfoTab::checkResize()
{
	if(!isRobust && drawBottom && bg.position.x < Stats::getScreenSize().x/2)
	{
		bg.position.x = 0;
		setupDrawspace();
	}

}


bool InfoTab::catchKey(KeyState key)
{
	switch(key.keyCode)
	{
		case KeyCodes::SHIFT:
			if(!isRobust)
				toggleRobust(); 
			else
				cycleToNext();
			return true;
			break;
		case KeyCodes::BACKSPACE:
			if(isRobust)
			{
				toggleRobust();
				return true;
			}
			break;
	}
	if(isRobust)
		return true;
	return false;
}



void InfoTab::draw()
{
	//add the bg
	addToDrawAbs(bg);
	addToDrawAbs(glorybg);
	//and draw all the contents of the font

	RECT tempDrawspace = drawspace;
	for(int i=0; i<currentInfo.size(); i++)
	{
		tempDrawspace.top += font->DrawTextA(0, currentInfo.at(i).c_str(), -1, &tempDrawspace, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(0,0,0,1));
	}


	string c = "Glory: ";

	char glor[64];
	itoa(PlayManager::getActivePlayer()->glory, glor, 10);
	c.append(glor);
	
	font->DrawTextA(0,c.c_str(),-1, &gloryDrawspace, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(0,0,0,1));
}

void InfoTab::setupBgSize()
{
	if(!isRobust)
	{
		TEXTMETRICA* textMetrics = new TEXTMETRICA();
		font->GetTextMetricsA(textMetrics);
		bg.scale.y = currentInfo.size() * textMetrics->tmHeight*1.2;
		bg.scale.x = 170*1.2;
		glorybg.scale.y = textMetrics->tmHeight*1.2;
		glorybg.scale.x = 100*1.2;
		delete textMetrics;
	}
	else
	{
		bg.scale.y = Stats::getScreenSize().y * .9;
		bg.scale.x = Stats::getScreenSize().x * .9;
		glorybg.scale.y = 0;
		glorybg.scale.x = 0;
	}
}

void InfoTab::setupBgPos()
{
	if(!isRobust)
	{
		//based on the camera position and the current cursor position, we can determine which quadrant of the screen the cursor is displayed
		//if the cursor is on the left, display the infotab/glorytab on the right and visa versa
		//the glorytab will always be on top and the infotab will always be on bottom

		//so first, get the cursor's position normalized to the view
		POINT normalized;
		normalized.x = currCell->position.x - Utility::camera->x;
		normalized.y = currCell->position.y - Utility::camera->y;

		drawRight = normalized.x <= Stats::getScreenSize().x/2;
		drawBottom = normalized.y <= Stats::getScreenSize().y/2;

		if(drawRight)
		{
			//if we're to draw on the right, then set the position to be the bg's scale away from the righthand side
			if(!drawBottom)
				bg.position.x = Stats::getScreenSize().x - bg.scale.x;
			else
				glorybg.position.x = Stats::getScreenSize().x - glorybg.scale.x;
		}
		else
		{
			//draw starting from the left, which is 0
			if(!drawBottom)
				bg.position.x = 0;
			else
				glorybg.position.x = 0;
		}

		bg.position.y = Stats::getScreenSize().y - bg.scale.y;
		glorybg.position.y = 0;
	}
	else
	{
		bg.position.x = Stats::getScreenSize().x *.05;
		bg.position.y = Stats::getScreenSize().y * .05;
	}
}

void InfoTab::setupDrawspace()
{
	if(!isRobust)
	{
		drawspace.left = bg.position.x+10; 
		drawspace.top = bg.position.y+5;
		gloryDrawspace.left = glorybg.position.x+10;
		gloryDrawspace.top = glorybg.position.y+1;
	}
	else
	{
		drawspace.left = bg.position.x+40; 
		drawspace.top = bg.position.y+40;
	}
}

void InfoTab::offsetDrawspace()
{
	
}

void InfoTab::gainFocus()
{

}