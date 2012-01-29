#include "StdAfx.h"
#include "TitleMenu.h"
#include "GameObject.h"
#include "BaseCode.h"
#include "MapSelectionMenu.h"

TitleMenu::TitleMenu(void) : UIMenu((GameObject*)NULL)
{
	generalInit();
	setupSprites();
}

TitleMenu::~TitleMenu(void)
{
}

void TitleMenu::setupOptions()
{
	title = L"Commander's Glory";
	addOption(L"Play Now!", 0);
	addOption(L"Choose Map!", 1);
	addOption(L"Exit", -1);
}

void TitleMenu::select(int id)
{
	switch(id)
	{
		case 0:
			PlayManager::newMap(Map::loadFromXML("peaisland.xml"));
			break;
		case 1:
			new MapSelectionMenu();
			return;
		case -1:
			killProgram();
			break;
	}
}

bool TitleMenu::catchKey(KeyState k)
{
	if(k.keyCode == KeyCodes::BACKSPACE)
		return true;
	return UIMenu::catchKey(k);
}

void TitleMenu::setupMenuDrawspace()
{
	drawSpace.left = 0;
	drawSpace.top = 0;
	drawSpace.right = Stats::getScreenSize().x;
	drawSpace.bottom = Stats::getScreenSize().y;
}

void TitleMenu::setupSprites()
{
	Utility::spriteFactory(&bg, L"infotab.png");
	Utility::spriteFactory(&mCursor, L"infotab.png");

	bg.position.z = ZOrdering::Menus;
	mCursor.position.z = ZOrdering::Menus - 1;

	bg.scale.x = drawSpace.right / bg.originalSize.x;
	bg.scale.y = drawSpace.bottom / bg.originalSize.y;
	bg.position.x = drawSpace.left;
	bg.position.y = drawSpace.top;
}


void TitleMenu::draw()
{
	addToDrawAbs(bg);

	RECT tempDrawSpace = drawSpace;
	long padding = (drawSpace.bottom - drawSpace.top) * .05;
	long top = (drawSpace.bottom - drawSpace.top) * .1;
	tempDrawSpace.top = top;

	top += FontManager::mainMenuFont->DrawTextW(0, title.c_str(), -1, &tempDrawSpace, DT_NOCLIP | DT_SINGLELINE | DT_CENTER, D3DXCOLOR(0, 0, 0, 1));
	top+= padding;
	tempDrawSpace.top = top;

	for(int i=0; i<optionNames.size(); i++)
	{
		top += FontManager::mainMenuFont->DrawTextW(0, optionNames.at(i).c_str(), -1, &tempDrawSpace, DT_NOCLIP | DT_SINGLELINE | DT_CENTER, D3DXCOLOR(0, 0, 0, 1));
		top+= padding;
		FontManager::mainMenuFont->DrawTextW(0, optionNames.at(i).c_str(), -1, &tempDrawSpace, DT_CALCRECT | DT_NOCLIP | DT_SINGLELINE | DT_CENTER, D3DXCOLOR(1, 1, 1, 1));
		
		if(i == optionSelection)
		{
			tempDrawSpace.left -= padding * .5;
			tempDrawSpace.right += padding * .5;
			tempDrawSpace.bottom += padding * .5;
			tempDrawSpace.top -= padding * .5;

			mCursor.position.x = tempDrawSpace.left;
			mCursor.position.y = tempDrawSpace.top;
			mCursor.scale.x = (tempDrawSpace.right - tempDrawSpace.left) / mCursor.originalSize.x;
			mCursor.scale.y = (tempDrawSpace.bottom - tempDrawSpace.top) / mCursor.originalSize.y;

			addToDrawAbs(mCursor);
		}

		tempDrawSpace = drawSpace;
		tempDrawSpace.top = top;
	}
}