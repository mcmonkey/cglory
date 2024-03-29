#pragma once
#include "stdafx.h"
#include "Tile.h"
#include "TileManager.h"
#include <vector>

using std::vector;
class Level
{
private:
	char name[256];
	int width;
	int height;
	
public:
	Level(char*, int, int);
	Level(void);
	Level(char*);
	~Level(void);
	void loadLevel(char*, TileManager*);
	void printLevel();
	vector<vector<Tile>> *terrain; 
};                                                                                                                                                                                                                                                                                                       