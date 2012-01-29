#include "StdAfx.h"
#include "Building.h"
#include "BuildingMenu.h"
#include "InformationStorage.h"
#include "Map.h"
#include "PlayManager.h"
#include "TerrainMenu.h"
#include <algorithm>

Building::Building(void)
{
	layer = CellLayers::Building;
	gloryMod = 1.0f;
	sightRange = 0;
}


GameObject* Building::copy()
{
	return new Building(*this);
}

Building::~Building(void)
{

}


bool Building::produce(int id)
{
	//TODO: Detract players money
	getOwner()->glory -= InformationStorage::unitTypes[id].cost;
	Unit* produced = container->owner->createUnit(id, owner->id, container->x, container->y);
	if(produced)
		produced->exhaust();
	return produced;
}

void Building::select()
{
	if(PlayManager::getActivePlayer() == this->owner)
		new BuildingMenu(this);
	else
		new TerrainMenu((Terrain*)container->objectAtLayer(CellLayers::Terrain)); // TODO Something
}

void Building::preTurn()
{
	//Add this building's gloryMod to the player's glory. 
	getOwner()->glory += gloryMod;
}

void Building::postTurn()
{
	//Doesn't do anything postTurn for now

}

void Building::giveInfo(vector<string>* infoCache)
{
	infoCache->push_back("Building");
	infoCache->push_back(name);
	string s = "Defense: ";
	char temp[255];
	itoa(defense,temp,10);
	s.append(temp);
	infoCache->push_back(s);
	s = "Health: ";
	s += health;
	s += "/";
	s += maxHealth;
	infoCache->push_back(s);
}

void Building::giveRobustInfo(vector<string>* infoCache)
{
	giveInfo(infoCache);
	infoCache->push_back(description);
	if(this->availableProduction.size() > 0)
	{
		infoCache->push_back("Production: ");
		for_each(availableProduction.begin(), availableProduction.end(), [&] (int id)
		{
			Unit* u = InformationStorage::getUnit(id);
			if(u)
			{
				string s;
				s = "   " + u->name + " (attack ";
				s += u->atk;
				s += ", defense ";
				s += u->defense;
				s += ") range ";
				s += u->minRange;
				s += "->";
				s += u->maxRange;

				infoCache->push_back(s);
				s = "      Cost: ";
				s += u->cost;
				infoCache->push_back(s);

				
				s = "      Can: ";
				if(u->canAmbush())
					s += "ambush, ";
				if(u->canBombard())
					s += "bombard, ";
				if(u->canCapture())
					s += "capture";
				infoCache->push_back(s);

				infoCache->push_back("");

			}
			delete u;
		});
	}
}