#pragma once
#include <string>
#include "GameSprite.h"
#include "Terrain.h"
#include "tinyxml.h"

using namespace std;

class Terrain;

// Holder class, should be created once per terrain type on startup, and stored in InformationStorage
class TerrainInfo
{
//------------------------ Members -------------------------------------
	
public:
	int			id;
	int			defense;
	int *		movementCosts;
	bool		grantsCover;

	string		name;
	GameSprite	sprite;
	
//------------------------ Methods -------------------------------------
public:
	TerrainInfo(void);
	~TerrainInfo(void);
	void factory(Terrain & t);
	void load(TiXmlNode*);
};

