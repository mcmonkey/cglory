#pragma once
#include "stdafx.h"
#ifndef TILE_H
#define TILE_H

class Tile
{

//------------------------ Stuff -------------------------------------
public:
	char name[256];		//The name of the tile
	int shorthand;		//The shorthand name of the tile, will be used as a key for a map in the TileManager class
	int defense;		//A value representing how much defense this tile provides
	int normPosX;		//The x-position of the tile on the spritesheet based on the number of tiles in the row, 0 indexed
	int normPosY;		//The y-position of the tile on the spritesheet based on the number of tiles in the column, 0 indexed
	Tile(const char*, int, int, float, float);
	Tile();				//Default constructor, makes empty tile
	~Tile();
	char* getName();
	int getDefense();
	int getNormPosX();
	int getNormPosY();
	void setName(const char*);
	void setDefense(int);
	void setNormPosX(int);
	void setNormPosY(int);
	void printTile();
	void copyTile(Tile);
	void giveName(char*);
	void giveShort(char*);
}; 
#endif