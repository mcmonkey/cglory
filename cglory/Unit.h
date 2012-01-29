#pragma once
#include <string>
#include <vector>
#include "PlayerOwned.h"
#include "TraversalCostHelper.h"
#include "Building.h"

// In seconds
#define UNIT_CELL_TO_CELL_TIME	.1f

using namespace std;

class Player;
class Cell;
class Unit : public PlayerOwned, CellEventListener
{
public:
	Unit(void);
	~Unit(void);

	//----------------------------
	//** MEMBERS **//
	//----------------------------
private:
	vector<Cell*>	currentPath;		// The path a unit is lerping over.
	int				currentPathIndex;	// The index in that path the unit is at.

	vector<Cell*>	ambushTargets;		// Collection of cells that this will ambush.

	bool			exhausted;
	bool			ambushing;
	bool			attacked;

public:
	int		atk;
	int		minRange;		//minRange and maxRange are mostly for units that can attack more than what is adjacent to them
	int		maxRange;
	int		movement;
	int		movementType;	//using an Enum to help readability 0=grassy, 1=road, 2=water, 3=mountain ....
	int		exp;

	bool	bombards;
	bool	ambushes;
	bool	captures;

	//----------------------------
	//** METHODS **//
	//----------------------------
public:
	GameObject* copy();
	void select(); //brings up the unitmenu

	void moveTowards(int dir);					// See namespace MoveDirections for input types.
	void followPath(vector<Cell*>);
	void targetForAmbush(vector<Cell*>);
	void releaseAmbushTargets();
	void exhaust();
	void blockedMovementOf(Unit & u);
	
	bool isExhausted();
	bool hasMoved();
	bool hasAttacked();

	bool canAmbush();
	bool canBombard();
	bool canCapture();
	
	vector<shared_ptr<CellPathNode>> cellsCanTravelTo();	// An array of available move spaces, with appropriate paths already laid out.
	vector<shared_ptr<CellPathNode>> cellsCanHit();			// An array of spaces that can be hit from this unit.
	vector<Cell*>					 cellsCanAmbush(int dir);
	
	bool visibleTo(Player & p);

	void draw();
	void update();

	// Traversal algorithms
	int movementTraverse(Cell* from, Cell* to);
	int attackTraverse(Cell* from, Cell* to);

	void attack(Unit* enemy);
	void capture(Building* building);
	void ambush(Unit* u);
	void bombard(Cell* c);
	void promote(int id);


	static int calculateDamage(Unit & attacker, Unit & defender);
	static int calculateDamage(Unit & attacker, Building & building);

	void preTurn();
	void postTurn();

	void objectPlaced(GameObject*);

	virtual void giveInfo(vector<string>* infoCache);		//returns a short list of information about the object

	virtual void giveRobustInfo(vector<string>* infoCache);	//returns a more detailed list of information about the object
};

typedef int (Unit::*UCostFunc)(Cell* f, Cell* t);

class UnitTraversalHelper : public TraversalCostHelper
{
private:
	Unit* attachedUnit;
	UCostFunc function;
public:
	virtual int cost(Cell* from, Cell* to);
	UnitTraversalHelper(Unit* attachedUnit, UCostFunc function);
};

