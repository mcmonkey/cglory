#pragma once
#include "stdafx.h"
#include "Tile.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <map>

class TileManager
{
private:
	std::map<int, Tile> tiles;
public:
	TileManager();
	~TileManager();
	Tile* returnTile(int);
	void loadTiles(const char*);
	void printTiles();
};                                                                                                                                                                                                                                                                                                                                                                       