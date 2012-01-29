#include "stdafx.h"
#include "Card.h"

Card::Card()
{
}

Card::~Card()
{
}

bool Card::execute()
{
	return true;
}

bool Card::execute(Building* b)
{
	bool played = true;
	for(int i=0; i<effects.size(); i++)
	{
		played = (played && effects[i]->execute(b));
	}
	return played;
}

bool Card::execute(Unit* u)
{
	bool played = true;
	for(int i=0; i<effects.size(); i++)
	{
		played = (played && effects[i]->execute(u));
	}
	return played;
}

bool Card::execute(Terrain* t)
{
	bool played = true;
	for(int i=0; i<effects.size(); i++)
	{
		played = (played && effects[i]->execute(t));
	}
	return played;
}

bool Card::execute(Player* p)
{
	bool played = true;
	for(int i=0; i<effects.size(); i++)
	{
		played = (played && effects[i]->execute(p));
	}
	return played;
}


//When passing a cell into execute, each effect will execute it's effect on the unit in the cell, the building in the cell, 
//the terrain in the cell, and the cell itself. 
bool Card::execute(Cell* c)
{
	bool played = true;
	for(int i=0; i<effects.size(); i++)
	{
		if(c->objectAtLayer(CellLayers::Unit))
			played = (played && effects[i]->execute((Unit*)c->objectAtLayer(CellLayers::Unit)));
		if(c->objectAtLayer(CellLayers::Building))
		{
			played = (played && effects[i]->execute((Building*)c->objectAtLayer(CellLayers::Building)));
			played = (played && effects[i]->execute(((Building*)c->objectAtLayer(CellLayers::Building))->getOwner()));
		}
		if(c->objectAtLayer(CellLayers::Terrain))
			played = (played && effects[i]->execute((Terrain*)c->objectAtLayer(CellLayers::Terrain)));
		played = (played && effects[i]->execute(c));
		played = (played && effects[i]->execute(c, owner));
	}
	return played;
}

bool Card::execute(Unit* u, Cell* c)
{
	bool played = true;
	for(int i=0; i<effects.size(); i++)
	{
		played = (played && effects[i]->execute(u, c));
	}
	return played;
}