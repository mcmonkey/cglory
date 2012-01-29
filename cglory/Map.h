#pragma once
#include "Cell.h"
#include <vector>
#include "TraversalCostHelper.h"
#include "Player.h"
#include "Unit.h"

class Cell;
class Player;

// Manages memory for:
//	Players
//	Cells
// (through create and destroy)
//	Units
//	Buildings

class Map
{
//------------------------ Members -------------------------------------
private:
	Cell** cellGrid;
	vector<Player*> players;

public:
	int width;
	int height;

	Unit* movingUnit;
	Cell* path;
	bool Map::currentlySlerping;

//------------------------ Methods -------------------------------------
private:
	bool placeNewPlayerOwned(PlayerOwned* g, int playerId, int x, int y); // Attempts to place a newly created object. Deletes it on fail.
	bool placeNewGameObject(GameObject* g, int x, int y);				 // Same as above.

public:
	// Creation
	// TODO Find a way to do these better through inheritance, maybe by attaching them to the gameobject heirarchy and passing in a map.
	Unit*		createUnit(int id, int playerId, int x, int y);		// Attempts to create a new unit on the map.
	Building*	createBuilding(int id, int playerId, int x, int y);	// Attempts to create a new building on the map.
	Terrain*	createTerrain(int id, int x, int y);

	// Cell Retrieval
	Cell*	getCell(int x, int y);
	Cell*	neighbor(Cell* c, int dir);

	// Moving units. From Jason: I want to move the graphic part of this to unit,
	void	continueSlerp();
	bool	moveUnitTo(int x1, int y1, int x2, int y2);
	
	// Game object Manipulation
	bool	destroyGameObject(GameObject* u);
	bool	placeGameObject(GameObject* g, int x, int y);

	// Player gets.
	Player*	getPlayer(int id);
	Player* getNeutral();
	
	// Returns number of actual players. (discounts neutral)
	int		playerCount();

	// BREADTH FIRST SEARCHES ARE AWESOME
	vector<shared_ptr<CellPathNode>>	reachableCells(Cell* origin, int range, TraversalCostHelper&);
	static vector<Cell*>				buildForwardPath(shared_ptr<CellPathNode> destination);

	static Map*	loadFromXML(char const * filename);
	Map(int inWidth, int inHeight, int playerCount);
	~Map(void);


};