#pragma once
#include <D3DX10.h>
#include "Player.h"
#include "CellPathNode.h"
#include "CellEventListener.h"
#include <set>

class Map;
class Player;
class CellPathNode;
class GameObject;

// Represents a part of the grid.
// Currently just keeps track of it's own x,y coordinates, and the terrain, building, and unit contained within.
class Cell
{
//------------------------ Members -------------------------------------
public:
	vector<GameObject*> layers;

	Map*				owner;

	set<CellEventListener*> listeners;

	// Represents the grid coordinates of this cell
	int x;			
	int y;

	// Represents the pixel coordinates of this cell.
	D3DXVECTOR3			position;	
	
	unsigned int		visibilityOverrides;	// Determines whether this cell is visible to a given player. (overrides visibilities)
	vector<int>			visibilities;			// List of how many units for a given player can see this cell.	

	// Used in traversals only. See Map::reachableCells
	// Normally is set to NULL
	shared_ptr<CellPathNode>		cNode;

//------------------------ Methods -------------------------------------
public:

	// Visibility functions that access and/or modify the visibilities mask.
	// Player is const as a reminder not to modify it.
	// Also, these are for FOG OF WAR, not whether or not it's on the screen.

	bool	visibleTo(Player const & p);

	// These two apply to the overrides.
	void	showTo(Player const & p);
	void	hideFrom(Player const & p);

	// These two apply to unit sight counting.
	void	addSight(Player const & p);
	void	removeSight(Player const & p);

	// The cumulative defense of all the objects in this cell.
	int		totalDefense();

	void	draw();
	void	update();

	void	setPosition(int x, int y);

	bool	addGameObject(GameObject & g);		// Fails on null g, or object already in that layer.
	bool	removeGameObject(GameObject & g);	// Fails if g is not the object at it's layer
	bool	replaceGameObject(GameObject & g);	// Fails if g is at an invalid layer.

	bool	removeGameObject(int layer);		// Returns false if there was no object at that layer, or layer out of bounds.

	GameObject*	objectAtLayer(int layer);		// Returns the object at the given layer, or NULL(0) if layer is out of bounds, or no object was there.
	GameObject*	top();							// Returns the topmost object. 

	void	registerListener(CellEventListener*);
	void	removeListener(CellEventListener*);
	void	notifyListeners(GameObject* g);

	Cell(void);
	~Cell(void);

private:
	inline bool validLayer(int layer);			// Returns whether the layer is a valid one. -DRD
};
