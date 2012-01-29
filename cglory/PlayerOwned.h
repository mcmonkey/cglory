#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Cell.h"
#include "TraversalCostHelper.h"

class Player;
class CellPathNode;

// Further extends the GameObject to include visibility and Player association.
class PlayerOwned : public GameObject
{
//------------------------ Members -------------------------------------
protected:
	Player*	owner;

	vector<shared_ptr<CellPathNode>> visibleCells;
	
	bool			sightCanChange;		// Prevents sight from changing. Applies mainly when moving.

public:
	int cost;
	int health;
	int maxHealth;
	int sightRange;

//------------------------ Methods -------------------------------------	
protected:
	void blind();			// Removes all sight from this object. Called before a move, upon a player switch (usually neutral->user)
	void grantVision();		// Returns all sight form this object.

public:
	void reevaluateVisibleCells();					// Helper function that calls blind and grantVision in succession.
	int	 visibilityTraverse(Cell* from, Cell* to);	// Returns one for now

	virtual void	setCell(Cell* c);	// Overrides to deal with vision.
	
	void	setOwner(Player * p);		// Sets the owner to p. Accepts null as meaning the owner is being removed.
	Player*	getOwner();			
	
	
	bool	isEnemy(PlayerOwned & other);	// Note: Returns true if other enemy has no player set.

	virtual void destroy();			// Overrides gameobject, and further takes care of player stuff.
	virtual void draw();			// Adds player number.

	virtual void preTurn() {};			//Takes care of things at the beginning of a turn
	virtual void postTurn() {};			//Takes care of things at the end of a turn

	PlayerOwned(void);
	~PlayerOwned(void);
};

typedef int (PlayerOwned::*PCostFunc)(Cell* f, Cell* t);

class POwnedTraversalHelper : public TraversalCostHelper
{
private:
	PlayerOwned* attachedUnit;
	PCostFunc function;
public:
	virtual int cost(Cell* from, Cell* to);
	POwnedTraversalHelper(PlayerOwned* attachedUnit, PCostFunc function);
};
