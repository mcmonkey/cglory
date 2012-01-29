#include "StdAfx.h"
#include "PlayManager.h"
#include "AdvanceScreen.h"
#include "InputManager.h"
#include "Sound.h"
#include "TitleMenu.h"
#include "WinScreen.h"

bool			PlayManager::drawFog = true;
bool			PlayManager::drawMap = true;

int				PlayManager::alivePlayerCount = 0;

Player*			PlayManager::activePlayer = NULL;
Map*			PlayManager::currentMap = NULL;
int				PlayManager::activePlayerIndex = 1;
InfoTab*		PlayManager::info;

void PlayManager::draw(int x, int y, int w, int h)
{
	if(currentMap && drawMap)
	{
		for(int i = 0; i < w && i + x< currentMap->width; i++)
		{
			for(int j = 0; j < h && j + y < currentMap->height; j++)
			{
				currentMap->getCell(i + x, j + y)->draw();
			}
		}
		info->draw();
	}
}

void PlayManager::drawAll()
{
	updateAll();
	if(currentMap)
	draw(0, 0, currentMap->width, currentMap->height);
	
}

void PlayManager::updateAll()
{
	if(currentMap)
	for(int i = 0; i <currentMap->width; i++)
	{
		for(int j = 0; j < currentMap->height; j++)
		{
			currentMap->getCell(i, j)->update();
		}
	}
}

void PlayManager::toggleMapDraw(bool set)
{
	drawMap = set;
}

void PlayManager::toggleMapDraw()
{
	drawMap = !drawMap;
}

void PlayManager::newMap(Map* m)
{
	if(!m)
	{
		DeveloperConsole::writeLine("Invalid map.");
		return;
	}

	alivePlayerCount = m->playerCount();

	// Remove old map.
	delete currentMap;
	activePlayerIndex = 0;
	activePlayer = m->getPlayer(activePlayerIndex);
	currentMap = m;
	drawFog = true;
	

	Stats::setMapsize(m->width * Stats::getTilesize(), m->height * Stats::getTilesize());
	InputManager::clearCatchers();

	info = new InfoTab();
	InputManager::mainCursor = new GameCursor();	

	advanceTurn();

	SoundManager::stopMusic();
	SoundManager::loopMusic("Rumble_Army.mp3");
}

Player* PlayManager::getActivePlayer()
{
	return activePlayer;
}

void PlayManager::advanceTurn()
{
	if(currentMap)
	{
		activePlayer->postTurn();
		
		do
		{
			activePlayerIndex++;
			if(activePlayerIndex > currentMap->playerCount())
				activePlayerIndex = 1;
			activePlayer = currentMap->getPlayer(activePlayerIndex);
		}
		while(!activePlayer->stillPlaying);

		activePlayer->preTurn();
		new AdvanceScreen();
	}
}

void PlayManager::gotoNeutralPlayer()
{
	activePlayer = currentMap->getPlayer(0);
}


Map* PlayManager::getCurrentMap()
{
	return currentMap;
}

void PlayManager::playerHasLost(Player* p)
{
	if(--alivePlayerCount == 1)
	{
		new WinScreen();
	}
	else
		;// TODO Display player eliminated

}

void PlayManager::toggleFogDraw()
{
	if(currentMap)
	{
		drawFog = !drawFog;
		for(int i = 0; i < currentMap->width; i++)
		{
			for(int j = 0; j < currentMap->height; j++)
			{
				currentMap->getCell(i, j)->visibilityOverrides = drawFog ? ~0x0 : 0x0;
			}
		}
	}
}

PlayManager::PlayManager(void)
{
}

void PlayManager::init()
{
	gotoMainMenu();
}

void PlayManager::gotoMainMenu()
{
	InputManager::clearCatchers();
	delete currentMap;
	currentMap = 0;
	toggleMapDraw(false);
	activePlayer = 0;
	new TitleMenu();
}
//PlayManager::newMap(Map::loadFromXML("map.xml"));

PlayManager::~PlayManager(void)
{
}


