#pragma once
#include <string>
#include "Cell.h"
#include "Player.h"
#include "AnimationStop.h"

class Cell;
class Player;
class Map;

using namespace std;

// Base object in the game. Can be put in a Cell, draw itself, and contribute to defense of the cell.
class GameObject
{
//------------------------ Members -------------------------------------
protected:	
	Cell*	container;

	AnimationStop* currentStop;

public:
	int		defense;	
	int		layer;		
	int		id;

	string	name;
	string	description;

	GameSprite gSprite;

//------------------------ Methods -------------------------------------
public:
	
	GameSprite*	getGSprite();	// Pointer to the the gamesprite.

	virtual void draw();		// Default. Draws itself relative to it's container, or at the origin if no container. Works off a temporary copy, can be called from overriden instances.
	virtual void update();		// Default, does nothing. Runs per frame, use for logic.
	
	void setStop(AnimationStop*);

	virtual void destroy();		// Used for destruction. Call pre-delete.

	virtual void setCell(Cell* c);		// Sets the container to c, or detaches it from a cell if c is null.
	Cell* getCell();					// Gets it the current cell.
	bool isIn(Cell* c);					// Returns whether c is the container for this.
	
	virtual void select() = 0;			// Called when this is selected on the map.

	virtual bool visibleTo(Player & p); // Default implementation always returns true. Override in unit mostly.

	virtual GameObject* copy() = 0;			// Returns a heap allocated copy of this.

	virtual void giveInfo(vector<string>* infoCache);		//returns a short list of information about the object

	virtual void giveRobustInfo(vector<string>* infoCache);	//returns a more detailed list of information about the object

	Map* getMap();						// Helper function, returns the map associated with this unit.

	GameObject(void);
	~GameObject(void);
};

