#include "stdafx.h"
#include "Level.h"
#include <iostream>

Level::Level()
{
}

Level::~Level()
{
}

Level::Level(char* inName, int inWidth, int inHeight)
{
	strcpy(name, inName); //Maybe change to strcpy_s
	width = inWidth;
	height = inHeight;
	terrain = new std::vector<vector<Tile>>();
	
	//Set up a default tile in every spot of the vector so we can properly access each spot of the grid
	Tile* tile;
	for(int i=0; i<inWidth; i++)
	{
		vector<Tile> row;
		for(int j=0; j<inHeight; j++)
		{
			tile = new Tile();
			row.push_back(*tile);
		}
		terrain->push_back(row);
	}
}

Level::Level(char* inName)
{
	strcpy(name, inName);
	width = -1;
	height = -1;
}

void Level::loadLevel(char* filename, TileManager* manager)
{
	TiXmlDocument doc( filename );
	if(doc.LoadFile())
	{
		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);
		pElem = hDoc.FirstChildElement().Element();
		hRoot=TiXmlHandle(pElem);

		//If width and height have not been handled yet
		if(width == -1 || height==-1)
		{
			TiXmlElement* pMapInfo = hRoot.FirstChild("Tiles").Element();
			pMapInfo->QueryIntAttribute("width", &width);
			pMapInfo->QueryIntAttribute("height", &height);
			terrain = new std::vector<vector<Tile>>();
			//Set up a default tile in every spot of the vector so we can properly access each spot of the grid
			Tile* tile;
			for(int i=0; i<width; i++)
			{
				vector<Tile> row;
				for(int j=0; j<height; j++)
				{
					tile = new Tile();
					row.push_back(*tile);
				}
				terrain->push_back(row);
			}
		}

		//block: Tiles
		TiXmlElement* pTileNode=hRoot.FirstChild( "Tiles" ).FirstChild().Element();
		for( pTileNode; pTileNode; pTileNode=pTileNode->NextSiblingElement())
		{
			int shortHand = 0;
			int tempX = 0;
			int tempY = 0;
			pTileNode->QueryIntAttribute("x", &tempX); // If this fails, original value is left as-is
			pTileNode->QueryIntAttribute("y", &tempY);
			pTileNode->QueryIntAttribute("shorthand", &shortHand);
			(terrain->at(tempX))[tempY] = *(manager->returnTile(shortHand));
			(terrain->at(tempX))[tempY].shorthand = shortHand;
		}
	}
	else
	{
		std::cout << "\nFailed to load the tiles\n";
	}
}

void Level::printLevel()
{
	for(int i=0; i<width; i++)
	{
		for(int j=0; j<width; j++)
		{
			(terrain->at(i))[j].printTile();
		}
	}
}