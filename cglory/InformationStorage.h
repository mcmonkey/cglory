#pragma once
#include "TerrainInfo.h"
#include "BuildingInfo.h"
#include "UnitInfo.h"
#include "CardInfo.h"
#include "Unit.h"
#include "Building.h"
#include "Map.h"
#include <map>
#include <string>

class MapSelectionMenu;

// Static class for grabbing unaltered info on terrain, units, and buildings.
// TerrainInfo, unitInfo, etc also derive from this class for their lock methods.
class InformationStorage
{

//------------------------ Static Members -------------------------------------
public:
	static map<int, TerrainInfo>		terrainTypes;		// List of terrain types
	static map<int, BuildingInfo>		buildingTypes;		// List of building types
	static map<int, UnitInfo>			unitTypes;			// List of unit types;
	static map<int, CardInfo>			cardTypes;			// List of card types


//------------------------ Static Methods -------------------------------------
public:
	// Uses the factor method to return a unit of the given id type.
	static Terrain *	getTerrain(int id);		
	static Unit *		getUnit(int id);	
	static Building *	getBuilding(int id);
	static Card*		getCard(int id);

	static void loadAll(string file);					// Call once at the beginning of the program to load all information in. 
														// (probably from Utility)
	static void saveMap(string file, Map *level);		// Call to save the state of the map.  Will save locations of terrain, buildings, and units, and who owns what units and buildings.
};

