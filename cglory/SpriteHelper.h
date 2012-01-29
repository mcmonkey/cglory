#pragma once
#include "GameSprite.h"
#include "Utility.h"
#include <map>
#include <string>

class SpriteHelper
{

public:
	// Stores gamesprites according to file name. Referenced by Utility::spriteFactory to prevent duplicate loading.
	static std::map<wstring, GameSprite> spriteStorage;

	static GameSprite fogOfWar;
	static GameSprite pathMarker;
	static GameSprite ambushOverlay;

	static void init();
};
