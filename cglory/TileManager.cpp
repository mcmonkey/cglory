#include "stdafx.h"
#include "TileManager.h"
#include <iostream>
#include <map>

TileManager::TileManager()
{
}
TileManager::~TileManager()
{
}

Tile* TileManager::returnTile(int tileShort)
{
	Tile *tile = new Tile();
//	std::cout << "Here's the tile we'll return: \n";
//	tiles[tileShort].printTile();
	/*strcpy(tile->shorthand, tiles[tileShort].shorthand);
	tile->defense = tiles[tileShort].defense;
	tile->normPosX = tiles[tileShort].normPosX;
	tile->normPosY = tiles[tileShort].normPosY;*/
	tile->copyTile(tiles[tileShort]);
	return tile;
}

void TileManager::loadTiles(const char* filename)
{
	TiXmlDocument doc( filename );
	if(doc.LoadFile())
	{
		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);
		pElem = hDoc.FirstChildElement().Element();
		hRoot=TiXmlHandle(pElem);
		//block: Tiles
		TiXmlElement* pTileNode=hRoot.FirstChild( "Tiles" ).FirstChild().Element();
		for( pTileNode; pTileNode; pTileNode=pTileNode->NextSiblingElement())
		{
			Tile t;
			const char *pName=pTileNode->Attribute("name");
			if (pName) t.setName(pName);
			pTileNode->QueryIntAttribute("shorthand", &t.shorthand);
			pTileNode->QueryIntAttribute("x", &t.normPosX); // If this fails, original value is left as-is
			pTileNode->QueryIntAttribute("y", &t.normPosY);
			pTileNode->QueryIntAttribute("defense", &t.defense);

			tiles.insert(std::pair<int, Tile>(t.shorthand, t));
		}
	}
	else
	{
		std::cout << "\nFailed to load the tiles\n";
	}
}

void TileManager::printTiles()
{
	std::map<int, Tile>::iterator it;
	for(it = tiles.begin(); it!=tiles.end(); it++)
	{
		Tile t = tiles[it->first];
		t.printTile();
	}
}