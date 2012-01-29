#include "StdAfx.h"
#include "WinScreen.h"

// This is really a dumb way to do it, but I can totally just leave these here.
GameSprite gSprite;
string winnerMessage;
WinScreen::WinScreen()
{
	Utility::spriteFactory(&gSprite, L"blackpixel.bmp");
	gSprite.position.x = 0;
	gSprite.position.y = 0;
	gSprite.scale.x = Stats::getScreenSize().x;
	gSprite.scale.y = Stats::getScreenSize().y;
	winnerMessage = "Player ";
	winnerMessage += (int)PlayManager::getActivePlayer()->id;
	winnerMessage += " wins!";
	PlayManager::toggleMapDraw(false);
	InputManager::registerCatcher(this);
}


WinScreen::~WinScreen(void)
{
}

void WinScreen::draw()
{
	addToDrawAbs(gSprite);
	RECT r;
	r.top = 0;
	r.left = 0;
	r.bottom = gSprite.scale.y;
	r.right = gSprite.scale.x;

	FontManager::mainMenuFont->DrawTextA(0, winnerMessage.c_str(), -1, &r, DT_NOCLIP | DT_VCENTER | DT_CENTER, D3DXCOLOR(1, 1, 1, 1));

}

void WinScreen::gainFocus(){}

bool WinScreen::catchKey(KeyState k)
{

	PlayManager::gotoMainMenu();
	return true;
}
