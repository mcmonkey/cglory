#include "StdAfx.h"
#include "Map.h"
#include <queue>
#include "Building.h"
#include "InformationStorage.h"

#define HQ_ID 0

Map::Map(int inWidth, int inHeight, int playerCount)
{
	width = inWidth;
	height = inHeight;
	currentlySlerping = false;

	cellGrid = new Cell * [width];
	for(int i = 0; i < width; i++)
	{
		cellGrid[i] = new Cell[height];
		for(int j = 0; j < height; j++)
		{
			cellGrid[i][j].setPosition(i, j);
			cellGrid[i][j].owner = this;
		}
	}

	for(int i = 0; i < playerCount + 1; i++)
	{
		players.push_back(new Player(i));
	}
}


Map::~Map(void)
{
	for(int i = 0; i < width; i++)
	{
		delete [] cellGrid[i];
	}
	delete [] cellGrid;

	while(players.size() > 0)
	{
		Player* p = players.back();
		players.pop_back();
		delete p;
	}
}

// Returns the cell at the given index, or NULL if x/y was out of range.
Cell* Map::getCell(int x, int y)
{
	if( x < 0 || x >= width || y < 0 || y >= height)
		return NULL;
	return cellGrid[x] + y;
}

// Gets a player of the given id.
Player* Map::getPlayer(int id)
{
	return players[id];
}

Player* Map::getNeutral()
{
	return getPlayer(0);
}

int Map::playerCount()
{
	return players.size() - 1;
}

// Gets a neighbor to a cell c. Based on direction dir (see MovementDirection namespace)
// Returns Null if:
//		c is NULL
//		The direction is off of the map
//		The direction isn't in MovementDirection
Cell* Map::neighbor(Cell* c, int dir)
{
	if(!c)
		return NULL;

	switch(dir)
	{
		case MovementDirection::DOWN:
			return getCell(c->x, c->y + 1);
		case MovementDirection::UP:
			return getCell(c->x, c->y - 1);
		case MovementDirection::LEFT:
			return getCell(c->x - 1, c->y);
		case MovementDirection::RIGHT:
			return getCell(c->x + 1, c->y);
		default:
			return NULL;
	}
}

bool Map::moveUnitTo(int x1, int y1, int x2, int y2)
{
	Cell orig = *getCell(x1, y1);
	Cell dest = *getCell(x2, y2);
	//implement some sort of pathfinding to figure out if its possible to get to that spot
	//if it can
	//set up the unit to slerp along the vector<Cell*> path to dest from orig and return true
	//if it can't
	//return false
	//--777--
	return false;
}
// Attempts to create a builduing at the specified location under ownership of the specified player.
// Returns false if their was a unit already there.
Building* Map::createBuilding(int id, int playerId, int x, int y)
{
	Cell* c;
	if(!(c = getCell(x, y)))
		return false;

	Building* b = InformationStorage::getBuilding(id);

	if(placeNewPlayerOwned(b, playerId, x, y))
	{
		if(id == HQ_ID)
			b->getOwner()->headquarters = b;
		return b;
	}
	return 0;
}

Unit* Map::createUnit(int id, int playerId, int x, int y)
{
	Cell* c;
	if(!(c = getCell(x, y)))
		return false;

	Unit* u = InformationStorage::getUnit(id);
	
	return placeNewPlayerOwned(u, playerId, x, y) ? u : 0;
}

Terrain* Map::createTerrain(int id, int x, int y)
{
	Cell* c;
	if(!(c = getCell(x, y)))
		return false;

	Terrain* t = InformationStorage::getTerrain(id);

	return placeNewGameObject(t, x, y) ? t : 0;
}

bool Map::placeNewPlayerOwned(PlayerOwned* g, int playerId, int x, int y)
{
	Player* p = getPlayer(playerId);
	if(!p)
	{
		delete g;
		return false;
	}
	if(placeNewGameObject(g, x, y))
	{
		p->giveObject(g);
		return true;
	}

	return false;

}

bool Map::placeNewGameObject(GameObject* g, int x, int y)
{
	if(placeGameObject(g, x, y))
	{
		return true;
	}
	
	delete g;
	return false;
}

// Attempts to place a building at a given coordinate.
// Returns false if the building can't be placed. (currently only due to another building being there)
bool Map::placeGameObject(GameObject* g, int x, int y)
{
	if(!g)
		return false;

	Cell* c = getCell(x, y);
	if(!c)
		return false;

	return c->addGameObject(*g);
}

bool Map::destroyGameObject(GameObject* g)
{
	bool result = false;
	if(g)
	{
		result = true;
		g->destroy();	
		delete g;
	}
	return result;
}

vector<Cell*> Map::buildForwardPath(shared_ptr<CellPathNode> destination)
{
	vector<Cell*> result;
	while(destination && destination->previousCell)
	{
		result.push_back(destination->cell);
		destination = destination->previousCell;
	}
	result.push_back(destination->cell);

	reverse(result.begin(), result.end());
	return result;
}

// Returns a vector of cells reachable from the origin cell, with the given "range" (which can be fuel, sight distance, etc) using the given cost function to traverse.
vector<shared_ptr<CellPathNode>> Map::reachableCells(Cell* origin, int range, TraversalCostHelper & cost)
{
	vector<Cell*> tested = vector<Cell*>();
	tested.reserve(range * range);
	
	queue<Cell*> breadthQueue = queue<Cell*>();
	
	// Set up origin node.
	origin->cNode = shared_ptr<CellPathNode>(new CellPathNode());
	origin->cNode->cell = origin;
	origin->cNode->costTo = 0;
	origin->cNode->previousCell = NULL;

	breadthQueue.push(origin);
	tested.push_back(origin);

	Cell* currentCell;
	while(breadthQueue.size() > 0)
	{
		currentCell = breadthQueue.front();
		breadthQueue.pop();

		Cell* childCell = NULL;
		int	  childCost = 0;
		// Loops trhough the four directions.
		for(int i = MovementDirection::DOWN; i < MovementDirection::Count; ++i)
		{
			// Finds the 'child', really just a neighbor, adjacent to the current.
			childCell = neighbor(currentCell, i);
			// Child will be null if we hit the edge.
			if(childCell) 
			{
				childCost = cost.cost(currentCell, childCell) + currentCell->cNode->costTo;
				// Check to make sure we don't exceed the allowed range.
				if(childCost <= range)
				{
					// It's within range, so if doesn't have an already better path, add it to this path,
					// and push it for evaluation. (possibly re-evaluation)
					
					// If the cell doesn't have a node association, it definitely needs one now!
					if(!childCell->cNode) 
					{
						childCell->cNode = shared_ptr<CellPathNode>(new CellPathNode());
						childCell->cNode->cell = childCell;
						childCell->cNode->costTo = childCost;
						childCell->cNode->previousCell = currentCell->cNode;
						breadthQueue.push(childCell);
						tested.push_back(childCell);
					}
					// Otherwise, make sure this is a shortest path.
					else if(childCell->cNode->costTo > childCost)
					{
						childCell->cNode->previousCell = currentCell->cNode;
						childCell->cNode->costTo = childCost;
						breadthQueue.push(childCell);
					}
				} // childCost < range
			} // childCell exists
		} // direction loop.
	}// Queue loop
	
	// Cleanup, and populate result at the same time.	
	vector<shared_ptr<CellPathNode>> result = vector<shared_ptr<CellPathNode>>();
	result.reserve(tested.size());
	
	for(vector<Cell*>::iterator i = tested.begin(); i < tested.end(); i++)
	{
		result.push_back(((*i)->cNode));
		(*i)->cNode.reset();
	}

	return result;
}

Map* Map::loadFromXML(char const * filename)
{
	TiXmlDocument doc( filename );
	
	if(doc.LoadFile())
	{
		int once = 1;
		Map* m;
		while(once == 1)
		{
			once = 0;
			TiXmlHandle hDoc(&doc);
			TiXmlElement* pElem;
			TiXmlHandle hRoot(0);
			pElem = hDoc.FirstChildElement().Element();
			hRoot=TiXmlHandle(pElem);

			//If initialize the map
			TiXmlElement* pMapInfo = hRoot.FirstChild("Tiles").Element();
			int width, height, players = -1;
			pMapInfo->QueryIntAttribute("width", &width);
			pMapInfo->QueryIntAttribute("height", &height);
			pMapInfo->QueryIntAttribute("playercount", &players);
			
			m = new Map(width, height, players);
			if(width < 0 || height < 0)
			{
				DeveloperConsole::write("Invalid dimensions "); DeveloperConsole::write(width); DeveloperConsole::write(" "); DeveloperConsole::writeLine(height);
				once = -1;
				break;
			}
			if(players < 1)
			{
				DeveloperConsole::writeLine("Invalid. Must have at least one player.");
				once = -1;
				break;
			}

			//block: Tiles
			TiXmlElement* pTileNode=hRoot.FirstChild( "Tiles" ).FirstChild().Element();
			int shortHand, tempX, tempY, pId = 0;
			for( pTileNode; pTileNode; pTileNode=pTileNode->NextSiblingElement())
			{
				shortHand = 0;
				tempX = 0;
				tempY = 0;
				pTileNode->QueryIntAttribute("x", &tempX); // If this fails, original value is left as-is
				pTileNode->QueryIntAttribute("y", &tempY);
				pTileNode->QueryIntAttribute("shorthand", &shortHand);
				
				if(!m->placeGameObject(InformationStorage::getTerrain(shortHand), tempX, tempY))
				{
					DeveloperConsole::write("Invalid terrain placement id "); DeveloperConsole::write(shortHand); DeveloperConsole::write(" at "); DeveloperConsole::write(tempX); DeveloperConsole::write(" "); DeveloperConsole::writeLine(tempY);
					once = -1;
					break;
				}
			}
			if(once == -1)break;

			//block: Units
			TiXmlElement* pUnitNode=hRoot.FirstChild("Units").FirstChild().Element();
			for( pUnitNode; pUnitNode; pUnitNode=pUnitNode->NextSiblingElement())
			{
				shortHand = 0;
				tempX = 0;
				tempY = 0;
				pId = 0;
				pUnitNode->QueryIntAttribute("x", &tempX);
				pUnitNode->QueryIntAttribute("y", &tempY);
				pUnitNode->QueryIntAttribute("id", &shortHand);
				pUnitNode->QueryIntAttribute("pId", &pId);
				if(!m->createUnit(shortHand, pId, tempX, tempY))
				{
					DeveloperConsole::write("Invalid unit placement id "); DeveloperConsole::write(shortHand); DeveloperConsole::write(" at "); DeveloperConsole::write(tempX); DeveloperConsole::write(" "); DeveloperConsole::writeLine(tempY);
					once = -1;
					break;
				}

			}
			if(once == -1)break;

			//block: Buildings
			TiXmlElement* pBuildingNode=hRoot.FirstChild("Buildings").FirstChild().Element();
			for(pBuildingNode; pBuildingNode; pBuildingNode=pBuildingNode->NextSiblingElement())
			{
				shortHand = 0;
				tempX = 0;
				tempY = 0;
				pId = 0;
				pBuildingNode->QueryIntAttribute("x", &tempX);
				pBuildingNode->QueryIntAttribute("y", &tempY);
				pBuildingNode->QueryIntAttribute("id", &shortHand);
				pBuildingNode->QueryIntAttribute("pId", &pId);
				if(!m->createBuilding(shortHand, pId, tempX, tempY))
				{
					DeveloperConsole::write("Invalid building placement id "); DeveloperConsole::write(shortHand); DeveloperConsole::write(" at "); DeveloperConsole::write(tempX); DeveloperConsole::write(" "); DeveloperConsole::writeLine(tempY);
					once = -1;
					break;
				}
			}

			//block: Cards
			TiXmlElement* pDeckNode = hRoot.FirstChild("Cards").FirstChild().Element();
			for(pDeckNode; pDeckNode; pDeckNode = pDeckNode->NextSiblingElement())
			{
				for(int j=1; j<=m->playerCount(); j++)
				{
					m->getPlayer(j)->addToDeck(atoi(pDeckNode->GetText()));
				}
			}
			if(once == -1)break;

			DeveloperConsole::writeLine();
			DeveloperConsole::write("Loaded new map with ");
			DeveloperConsole::write(m->players.size() - 1);
			DeveloperConsole::write(" players with grid size ");
			DeveloperConsole::write(m->width);
			DeveloperConsole::write(", ");
			DeveloperConsole::writeLine(m->height);
			return m;
		}
		if(once == -1)
			delete m;
	}
	else
	{
		DeveloperConsole::writeLine();
		DeveloperConsole::write("Failed to load ");
		DeveloperConsole::write(filename);
		DeveloperConsole::writeLine(".");
	}
	return NULL;
}