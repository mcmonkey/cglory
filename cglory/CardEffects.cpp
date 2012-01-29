#include "stdafx.h"
#include "CardEffects.h"
#include "InformationStorage.h"
#include "Building.h"
#include "Unit.h"
#include "Terrain.h"

StatChanger::StatChanger()
{
}

//Changes the stat of a unit
bool StatChanger::execute(Unit* u)
{
	//Determine which stat we are changing, and change the unit's stat based on the modifier
	switch(stat)
	{
	case GameStats::Attack:
		u->atk += modifier;
		return true;
		break;
	case GameStats::Defense:
		u->defense += modifier;
		return true;
		break;
	case GameStats::Health:
		u->health += modifier;
		u->health = min(u->health, u->maxHealth);
		return true;
		break;
	case GameStats::MaxHealth:
		u->maxHealth += modifier;
		return true;
		break;
	case GameStats::MaxRange:
		u->maxRange += modifier;
		return true;
		break;
	case GameStats::MinRange:
		u->minRange += modifier;
		return true;
		break;
	case GameStats::Movement:
		u->movement += modifier;
		return true;
		break;
	case GameStats::Sight:
		u->sightRange += modifier;
		return true;
		break;
	}
	return false;
}

//Changes the stat of a building
bool StatChanger::execute(Building* b)
{
	//Determine the stat to change, and then change the stat based on modifier
	switch(stat)
	{
	case GameStats::Defense:
		b->defense += modifier;
		return true;
		break;
	case GameStats::GloryMod:
		b->gloryMod += modifier;
		return true;
		break;
	case GameStats::Health:
		b->health += modifier;
		b->health = min(b->health, b->maxHealth);
		return true;
		break;
	case GameStats::Sight:
		b->sightRange += modifier;
		return true;
		break;
	}
	return false;
}

//Promote a unit if it has enough experience and is of the appropriate type
bool UnitPromoter::execute(Unit* u)
{
	if(u->exp >= expReq)
	{
		for(int i=0; i<legalIDs.size(); i++)
		{
			if(u->id == legalIDs[i])
			{
				//Replaces the unit with a new type of unit under control of the player
				Player* owner = u->getOwner();
				Cell* cell = u->getCell();
				cell->removeGameObject(CellLayers::Unit);
				PlayManager::getCurrentMap()->createUnit(newUnitID, owner->id, cell->x, cell->y);
				return true;
			}
		}
	}
	return false;
}

//Removes glory from Player p; ensures that glory is at least 0
bool GloryRemover::execute(Player* p)
{
	p->glory -= gloryMod;
	p->glory = max(p->glory, 0);
	return true;
}

//Forces Player p to discard numCards random cards from their hand.
bool CardDiscarder::execute(Player* p)
{
	for(int i=0; i<numCards; i++)
	{
		p->discardCard();
	}
	return true;
}

//Creates a building or unit at Cell c under Player p's control, or
//replaces the terrain at Cell c with new terrain
bool ObjectProducer::execute(Cell* c, Player* p)
{
	GameObject* gObj;
	//Determine if we are adding a building, unit, or terrain
	switch(layer)
	{
	case CellLayers::Building:
		gObj = InformationStorage::getBuilding(id);
		((PlayerOwned*)gObj)->setOwner(p);
		return c->addGameObject(*gObj);
		break;
	case CellLayers::Unit:
		gObj = InformationStorage::getUnit(id);
		((PlayerOwned*)gObj)->setOwner(p);
		return c->addGameObject(*gObj);
		break;
	case CellLayers::Terrain:
		//Slightly different, because this will overwrite terrain
		gObj = InformationStorage::getTerrain(id);
		c->removeGameObject(CellLayers::Terrain);
		PlayManager::getCurrentMap()->createTerrain(id, c->x, c->y);
		return true;
		break;
	}
	return false;
}

bool SpecialAttack::execute(Unit* u, Cell* c)
{
	return true;
}

bool BurstAttack::execute(Unit* u, Cell* c)
{
	return true;
}

bool LineAttack::execute(Unit* u, Cell* c)
{
	return true;
}