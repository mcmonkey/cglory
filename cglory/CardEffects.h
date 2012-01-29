#pragma once

class Building;
class Unit;
class Terrain;
class Player;
class Cell;

class CardEffect
{
	//--------------------------Methods----------------------------
public:
	//Declare multiple empty execute methods, overwrite only the ones needed in each type of Card effect
	virtual bool execute(Building* b){return true;};
	virtual bool execute(Unit* u){return true;};
	virtual bool execute(Terrain* t){return true;};
	virtual bool execute(Player* p){return true;};
	virtual bool execute(Cell* c){return true;};
	virtual bool execute(Unit* u, Cell* c){return true;};
	virtual bool execute(Cell* c, Player* p){return true;};
};


//This class will change a unit or buildings stat by a certain value, and can also limit its legal targets
class StatChanger : CardEffect
{
	//---------------Members------------------
public:
	std::vector<int> legalIDs;		//The IDs of legal targets of this card
	int stat;						//Which stat to change, uses NameSpaces::GameStats
	int modifier;					//What number will be added to the stat
	int layer;						//What layer this is affecting(unit/building), uses NameSpaces::CellLayers
	StatChanger();

	//--------------Methods-----------------
public:
	bool execute(Building* b);		//Changes the stat of a building
	bool execute(Unit* u);			//Changes the stat of a unit
};

//This class will promote a unit into another unit if it has the required experience and is of one of the legalIds
class UnitPromoter : CardEffect
{
public:
	std::vector<int> legalIDs;		//What unit IDs are allowed to be promoted
	int expReq;						//The amount of experience required to promote this unit
	int newUnitID;					//What the unit will promote into

	bool execute(Unit* u);			//Takes in a pointer to the unit to promote
};

//A class that will remove glory from a player
class GloryRemover : CardEffect
{
public:
	int gloryMod;					//How much glory the player will lose
									//NOTE: This should be a positive number unless you want to GIVE the player glory. 
									//This class REMOVES this much glory.

	bool execute(Player* p);		//Takes a pointer to the player to deduct glory from
};

//A class that will force an opponent to discard cards at random
class CardDiscarder : CardEffect
{
public:
	int numCards;					//The number of cards the player will discard

	bool execute(Player* p);		//A pointer to the player that will discard cards
};

//A class that will produce a game object at a specific location. The object can be a unit, building, or terrain.
//If it's terrain, it will replace the terrain that is in that cell. 
//If it's a unit or building, the built object will be owned by the player who played the card
class ObjectProducer : CardEffect
{
public:
	int id;								//The id of the unit/building/terrain
	int layer;							//The layer, which will also tell us if it's a unit, building, or terrain

	bool execute(Cell* c, Player* p);	//Takes in the cell to place the object, and the player who will own it(Stored in Card class)
};

//Special Attack effect, stores what can use this attack and the stats of the attack
class SpecialAttack : CardEffect
{
public:
	std::vector<int> legalAttackers;	//The IDs of units that can perform this attack
	int minRange;						//The minRange of this attack, similar to a unit's minRange
	int maxRange;						//The maxRange of this attack
	int damage;							//The amount of damage this attack will deal
	int heal;							//The amount of damage this action will heal, allowing us to make "First Aid" type cards

	bool execute(Unit* u, Cell* c);
};

//A special type of special attack, hits enemies within x squares of destination cell
class BurstAttack : public SpecialAttack
{
public:
	int burst;							//The number of squares away from the center that this attack will spread

	bool execute(Unit* u, Cell* c);		
};

//A special type of attack that will continue in a straight line until it hits up to maxTargets enemies
class LineAttack : public SpecialAttack
{
public:
	int maxTargets;						//The maximum number of targets this attack can hit.

	bool execute(Unit* u, Cell* c);
};