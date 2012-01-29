#include "StdAfx.h"
#include "InformationStorage.h"
#include "Utility.h"
#include "MapSelectionMenu.h"

map <int, UnitInfo> InformationStorage::unitTypes;
map <int, TerrainInfo> InformationStorage::terrainTypes;
map <int, BuildingInfo> InformationStorage::buildingTypes;
map <int, CardInfo> InformationStorage::cardTypes;

Unit* InformationStorage::getUnit(int id)
{
	if(unitTypes.find(id) != unitTypes.end())
	{
		Unit* u = new Unit();
		unitTypes[id].factory(u);
		return u;
	}
	return 0x0;
}

Terrain* InformationStorage::getTerrain(int id)
{
	if(terrainTypes.find(id) != terrainTypes.end())
	{
		Terrain* t = new Terrain();
		terrainTypes[id].factory(*t);
		return t;
	}
	return 0x0;
}

Building* InformationStorage::getBuilding(int id)
{
	if(buildingTypes.find(id) != buildingTypes.end())
	{
		Building* b = new Building();
		buildingTypes[id].factory(b);
		return b;
	}
	return 0x0;
}

Card* InformationStorage::getCard(int id)
{
	if(cardTypes.find(id) != cardTypes.end())
	{
		Card* c = new Card();
		cardTypes[id].factory(c);
		return c;
	}
}

void InformationStorage::loadAll(string file)
{
	//Clear out the object types first
	terrainTypes.clear();
	buildingTypes.clear();
	unitTypes.clear();
	
	TiXmlDocument doc( file.c_str());
	if(doc.LoadFile())
	{
		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);
		pElem = hDoc.FirstChildElement().Element();
		hRoot=TiXmlHandle(pElem);


		//--------------------------------Load in Units----------------------

		TiXmlNode* pUnitNode=hRoot.FirstChild( "Units" ).FirstChild().ToNode();
		TiXmlNode* pUnitInfoNode;
		//For loop will cycle through each unit within the Units tag
		for( pUnitNode; pUnitNode; pUnitNode=pUnitNode->NextSiblingElement())
		{
			//Need to iterate through the data of a unit; can make a pointer to the first child of pUnitNode for ID, get NextSiblingElement for other elements, use 
			//query attributes for combat stats.
			UnitInfo u = UnitInfo();
			u.load(pUnitNode);
			unitTypes[u.id] = u;
		}



		//----------------------Load in Terrain-------------------------------

		TiXmlNode* pTerrainNode=hRoot.FirstChild( "Terrain" ).FirstChild().ToNode();
		TiXmlNode* pTerrainInfoNode;
		//For loop will cycle through each unit within the Units tag
		for( pTerrainNode; pTerrainNode; pTerrainNode=pTerrainNode->NextSiblingElement())
		{
			//Need to iterate through the data of a unit; can make a pointer to the first child of pUnitNode for ID, get NextSiblingElement for other elements, use 
			//query attributes for combat stats.
			TerrainInfo t = TerrainInfo();
			t.load(pTerrainNode);
			terrainTypes[t.id] = t;
		}


		//---------------------------------Load in Buildings--------------------------------------

		TiXmlNode* pBuildingNode=hRoot.FirstChild( "Buildings" ).FirstChild().ToNode();
		//TiXmlNode* pBuildingInfoNode;
		//TiXmlNode* pProductionIDNode;
		//For loop will cycle through each unit within the Units tag
		for( pBuildingNode; pBuildingNode; pBuildingNode=pBuildingNode->NextSiblingElement())
		{
			//Need to iterate through the data of a unit; can make a pointer to the first child of pUnitNode for ID, get NextSiblingElement for other elements, use 
			//query attributes for combat stats.
			BuildingInfo b = BuildingInfo();
			b.load(pBuildingNode);
			buildingTypes[b.id] = b;
		}

		//-------------------------------Load in Commander Cards--------------------------------
		TiXmlNode* pCardNode = hRoot.FirstChild( "Cards" ).FirstChild().ToNode();
		for( pCardNode; pCardNode; pCardNode=pCardNode->NextSiblingElement())
		{
			CardInfo c = CardInfo();
			c.load(pCardNode);
			cardTypes[c.id] = c;
		}


	}
	else
	{
		//std::cout << "\nFailed to load the units\n";
	}

	DeveloperConsole::write("Buildings Loaded: ");
	DeveloperConsole::writeLine(buildingTypes.size());
	DeveloperConsole::write("Units Loaded: ");
	DeveloperConsole::writeLine(unitTypes.size());
	DeveloperConsole::write("Terrain Loaded: ");
	DeveloperConsole::writeLine(terrainTypes.size());
	

}

//Saves the map.  Good for editing maps, not good for saving a game in mid-play because unit statuses are not saved. 
void InformationStorage::saveMap(string filename, Map *level)
{
	TiXmlDocument doc;
	string s;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	//Set up the root of the XML document
	TiXmlElement *root = new TiXmlElement("TileInfo");
	doc.LinkEndChild(root);

	//Set up the Units, Buildings, and Tiles blocks
	TiXmlElement *units = new TiXmlElement("Units");
	TiXmlElement *buildings = new TiXmlElement("Buildings");
	TiXmlElement *tiles = new TiXmlElement("Tiles");

	//Set up pointers to be used throughout saving the map
	TiXmlElement *elem;
	GameObject *gObj = 0;
	Unit *unit = 0;
	Building *building = 0;
	Terrain *tile = 0;

	//Set the width, height, and player count in the XML based on the level
	tiles->SetAttribute("width", level->width);
	tiles->SetAttribute("height", level->height);
	tiles->SetAttribute("playercount", level->playerCount());

	//Add the units, buildings, and tiles blocks to the root
	root->LinkEndChild(units);
	root->LinkEndChild(buildings);
	root->LinkEndChild(tiles);

	Cell* cell;
	
	//Go through every cell of the map, and check what the terrain, unit(if any), and building(if any)
	//there is, and store it in the xml
	for(int i=0; i<level->width; i++)
	{
		for(int j=0; j<level->height; j++)
		{
			cell = level->getCell(i, j);
			gObj = cell->objectAtLayer(CellLayers::Unit);
			if(gObj)
			{
				//Add the unit to the units tag
				unit = (Unit*)gObj;
				elem = new TiXmlElement("Unit");
				elem->SetAttribute("id", unit->id);
				elem->SetAttribute("pId", unit->getOwner()->id);
				elem->SetAttribute("x", i);
				elem->SetAttribute("y", j);
				units->LinkEndChild(elem);
			}

			gObj = cell->objectAtLayer(CellLayers::Building);
			if(gObj)
			{
				//Add the building to the buildings tag
				building = (Building*)gObj;
				elem = new TiXmlElement("Building");
				elem->SetAttribute("id", building->id);
				elem->SetAttribute("pId", building->getOwner()->id);
				elem->SetAttribute("x", i);
				elem->SetAttribute("y", j);
				buildings->LinkEndChild(elem);
			}
			//Don't bother checking for terrain, there should always be one there.

			gObj = cell->objectAtLayer(CellLayers::Terrain);
			tile = (Terrain*)gObj;
			elem = new TiXmlElement("Tile");
			elem->SetAttribute("shorthand", tile->id);
			elem->SetAttribute("x", i);
			elem->SetAttribute("y", j);
			tiles->LinkEndChild(elem);
		}
	}
	doc.SaveFile(filename.c_str());
	
}