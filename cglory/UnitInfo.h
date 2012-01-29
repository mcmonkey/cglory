#pragma once
#include <string>
#include "Unit.h"
#include "tinyxml.h"

using namespace std;

class Unit;

class UnitInfo
{
public:
	UnitInfo(void);
	~UnitInfo(void);

	//------------------
	// **MEMBERS** //
	//------------------

	int atk;
	int def;
	int minRange;
	int maxRange;
	int health;
	string name;
	string description;
	GameSprite sprite;
	int movement;
	int movementType;
	int id;
	int cost;
	int sightRange;

	// Represent booleans
	int ambushes;
	int captures;
	int bombards;

	//-----------------
	// **METHODS** //
	//-----------------

	void factory(Unit *u);
	void load(TiXmlNode*);
};

