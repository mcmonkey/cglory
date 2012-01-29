#include "StdAfx.h"
#include "AdvanceScreen.h"
#include "InputManager.h"
#include "PlayManager.h"
#include "Utility.h"

AdvanceScreen::AdvanceScreen(void)
{
	generalInit();
}


AdvanceScreen::~AdvanceScreen(void)
{
}

void AdvanceScreen::gainFocus()
{

}

void AdvanceScreen::generalInit()
{
	Utility::spriteFactory(&bg, L"blackpixel.bmp");
	bg.scale.x = Stats::getScreenSize().x;
	bg.scale.y = Stats::getScreenSize().y;
	
	char temp[64];
	itoa(PlayManager::getActivePlayer()->id, temp, 10);
	
	message = "Player ";
	message.append(temp);
	message.append(" please press space.");

	Utility::fontFactory(20, L"Consolas", &consoleFont);
	drawSpace.top = 0;
	drawSpace.left = 0; //50 is the size of each character, there are 8 characters, and it should be centered
	drawSpace.bottom = Stats::getResolution().y;
	drawSpace.right = Stats::getResolution().x;

	InputManager::registerCatcher(this);
	PlayManager::toggleMapDraw(false);
}

void AdvanceScreen::select()
{
	PlayManager::toggleMapDraw(true);
	InputManager::removeCatcher();
}

void AdvanceScreen::draw()
{
	addToDrawAbs(bg);
	
	consoleFont->DrawTextA(0, message.c_str(), -1, &drawSpace, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER, D3DXCOLOR(1,1,1,1));
}

bool AdvanceScreen::catchKey(KeyState key)
{
	//overriding InputCatcher::catchKey to serve functionality here
	switch(key.keyCode)
	{
	case KeyCodes::SPACE:
			select();		   return true;
	}
	return true;
}