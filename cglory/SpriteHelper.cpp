#include "stdafx.h"
#include "SpriteHelper.h"

GameSprite SpriteHelper::fogOfWar;
GameSprite SpriteHelper::pathMarker;
GameSprite SpriteHelper::ambushOverlay;

map<wstring, GameSprite> SpriteHelper::spriteStorage;

void SpriteHelper::init()
{
	Utility::spriteFactory(&fogOfWar, L"fog.png");
	Utility::spriteFactory(&pathMarker, L"path.png");
	Utility::spriteFactory(&ambushOverlay, L"ambush.png");
}