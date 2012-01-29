#include "StdAfx.h"
#include "Terrain.h"
#include "TerrainMenu.h"


Terrain::Terrain(void)
{
	layer = CellLayers::Terrain;
}

GameObject* Terrain::copy()
{
	return new Terrain(*this);
}

Terrain::~Terrain(void)
{
}

void Terrain::select()
{
	//TODO: Stuff.
	new TerrainMenu(this);
}

void Terrain::giveInfo(vector<string>* infoCache)
{
	infoCache->push_back("Terrain");
	infoCache->push_back(name);
	string s = "Defense: ";
	char temp[255];
	itoa(defense,temp,10);
	s.append(temp);
	infoCache->push_back(s);
}

void Terrain::giveRobustInfo(vector<string>* infoCache)
{
	giveInfo(infoCache);
	infoCache->push_back(description);
}