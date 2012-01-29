#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include "InformationStorage.h"
#include "InfoTab.h"

class PlayManager
{
//------------------------ Members -------------------------------------
public:
	static bool				drawFog;
	static InfoTab*			info;
	
private:
	static Map*				currentMap;		// The level being run.
	static Player*			activePlayer;	// The player that is currently in control.
	static int				activePlayerIndex; // That player's index.
	static bool				drawMap;

	static int				alivePlayerCount;

//------------------------ Methods -------------------------------------
private:
	static void				postTurn();
	static void				preTurn();

public:
	// Gameplay

	static void newMap(Map* m);
	
	static Player*	getActivePlayer();
	static Map*		getCurrentMap();

	static void		advanceTurn();
	static void		init();

	static void		gotoMainMenu();
	
	static void		playerHasLost(Player* p);
	
	// TODO Remove these after testing use.
	// Do not call normally. Only used for editor
	static void		gotoNeutralPlayer();
	static void		toggleFogDraw();

public:	
	// Drawing
	static void draw(int x, int y, int w, int h);	// Draws the current map
	static void drawAll();							// Draws the whole map
	static void updateAll();

	static void toggleMapDraw(bool set);
	static void toggleMapDraw();
	

	PlayManager(void);
	~PlayManager(void);
};

