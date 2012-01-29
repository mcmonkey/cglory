#pragma once
#include <string>
#include <vector>
#include "Building.h"
#include "GameSprite.h"
#include "tinyxml.h"

using namespace std;

class Building;

// Holder class, should be created once per terrain type on startup, and stored in InformationStorage
class BuildingInfo
{
//------------------------ Members -------------------------------------
private:
	

public:
	int			id;
	int			defense;
	int			gloryMod;
	int			health;
	string		name;
	GameSprite	sprite;
	vector<int>	productionIds; // Vector of unit id's that can be produced by this building type. Maybe be empty.

//------------------------ Methods -------------------------------------
public:
	BuildingInfo(void);
	~BuildingInfo(void);
	void factory(Building* b);
	void load(TiXmlNode*);
};