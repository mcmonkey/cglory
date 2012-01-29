#include "stdafx.h"
#include "Unit.h"
#include "UnitMenu.h"
#include "Sound.h"
#include "Terrain.h"
#include "Map.h"
#include <algorithm>
#include "CellLerpAnimation.h"
#include "PlayManager.h"
#include "TerrainMenu.h"

Unit::Unit(void)
{
	atk = 3;
	defense = 4;
	minRange = 1;
	maxRange = 1;
	health = 10;
	exp = 0;
	name = "trooper";
	description = "this guy is a default";
	movement = 210;
	movementType = MovementType::FOOT;
	cost = 500;
	id = 0;
	owner = 0;
	container = 0x0;
	sightRange = 3;
	layer = CellLayers::Unit;
	currentPathIndex = 0;
	ambushing = false;
	exhausted = false;
}

GameObject* Unit::copy()
{
	return new Unit(*this);
}

Unit::~Unit(void)
{
}

void Unit::select()
{
	if(PlayManager::getActivePlayer() == this->owner)
	{
		//if the currentplayer owns this unit, then open his menus
		//SoundManager::loopMusic("Juese.mp3");
		new UnitMenu(this);
	}
	else
		new TerrainMenu((Terrain*)container->objectAtLayer(CellLayers::Terrain));// TODO: Something
}

void Unit::moveTowards(int dir)
{
	// Eventually this method should BEGIN slerping the sprite in the appropriate direction.
	// Also would set slerping to true, which would then be set back to false in update upon completion
}


// Draws the unit, taking into account the current player visibility.
void Unit::draw()
{
	PlayerOwned::draw();
	
	// Draws a number indicating the current owner.
	D3DXVECTOR3 absPosition = -*Utility::camera + container->position;
	RECT r = RECT();
	r.left = absPosition.x;
	r.top = absPosition.y;
	r.right = r.left + Stats::getTilesize();
	r.bottom = r.top + Stats::getTilesize();
	char temp[64];
	
	string hpbar;
	itoa(this->health, temp, 10);
	hpbar.append(temp);
	hpbar.append(" / ");
	itoa(this->maxHealth, temp, 10);
	hpbar.append(temp);
	
	FontManager::cellFont->DrawTextA(0, hpbar.c_str(), -1, &r, DT_NOCLIP | DT_BOTTOM | DT_RIGHT, D3DXCOLOR(1, 1, 1, 1));
}

void Unit::update()
{
	GameObject::update();
	if(!currentStop)
	{
		if(currentPathIndex < ((int)currentPath.size() - 1))
		{
			// Disable sight until the end.
			if(currentPathIndex == 0)
				sightCanChange = false;

			Unit* block;
			if((block = (Unit*)currentPath[++currentPathIndex]->objectAtLayer(CellLayers::Unit)) && block->isEnemy(*this))
			// Null check and check if the unit is an enemy which would block movement.
			{
				// TODO: Fail animation
				// Ends the path following.
				exhaust();
				block->blockedMovementOf(*this);
				
				sightCanChange = true;
				reevaluateVisibleCells();
				
			}
			else
			{
				if(currentPathIndex == ((int)currentPath.size() - 1))
				{
					sightCanChange = true;
				}
				// Continue on to the next place.
				D3DXVECTOR3 from = gSprite.position;
				currentPath[currentPathIndex]->addGameObject(*this);
				D3DXVECTOR3 to = gSprite.position;
				setStop(new CellLerpAnimation(&gSprite, from, to, Stats::getTilesize() / UNIT_CELL_TO_CELL_TIME));
				// Made it to the end, reenable sight
				
			}
		}
	}
}

void Unit::objectPlaced(GameObject* g)
{
	if(g->layer == CellLayers::Unit)
	{
		Unit* u = (Unit*)g;
		if(ambushing && u->isEnemy(*this))
		{
			attack(u);
			u->exhaust();
			ambushing = false;
		}
	}
}

void Unit::preTurn()
{
	exhausted = false;
	ambushing = false;
	attacked = false;

	releaseAmbushTargets();

	currentPath.clear();
	currentPathIndex = 0;
}

void Unit::postTurn()
{

}

void Unit::exhaust()
{
	exhausted = true;
	currentPath.clear(); // Ends movement if it's currently happening.
}

void Unit::blockedMovementOf(Unit & u)
{
	// TODO: ALERT player to presence of this unit.
	ambushing = false;
}

bool Unit::isExhausted()
{
	return exhausted || (hasMoved() && hasAttacked());
}

bool Unit::hasMoved()
{
	return currentPathIndex;
}

bool Unit::hasAttacked()
{
	return attacked;
}

bool Unit::canAmbush()
{
	return ambushes;
}

bool Unit::canBombard()
{
	return bombards;
}

bool Unit::canCapture()
{
	return captures;
}

bool Unit::visibleTo(Player & p)
{
	return container->visibleTo(p) && (!ambushing || (p.id == owner->id));
}

void Unit::followPath(vector<Cell*> path)
{
	currentPath = path;
	currentPathIndex = 0;
}

void Unit::releaseAmbushTargets()
{
	for(auto i = ambushTargets.begin(); i < ambushTargets.end(); ++i)
	{
		(*i)->removeListener(this);
	}

	ambushTargets.clear();
}

void Unit::targetForAmbush(vector<Cell*> targets)
{
	releaseAmbushTargets();
	if(targets.size() > 0)
	{
		for(auto i = targets.begin(); i < targets.end(); ++i)
		{
			(*i)->registerListener(this);
		}
		exhaust();
		ambushing = true;
		ambushTargets =  targets;
	}
}

void Unit::attack(Unit* enemy)
{
	attacked = true;
	enemy->health -= calculateDamage(*this, *enemy);
	if(enemy->health <= 0)
	{
		getMap()->destroyGameObject(enemy);
		exp ++;
	}
	else
	{
		//Check for counter attack
		int xDist = abs(enemy->getCell()->x - container->x);
		int yDist = abs(enemy->getCell()->y - container->y);
		if(xDist + yDist <= enemy->maxRange && xDist + yDist >= enemy->minRange)
		{
			health -= calculateDamage(*this, *enemy);
			if(health <= 0)
			{
				getMap()->destroyGameObject(this);
			}
		}
	}
}

void Unit::bombard(Cell* c)
{
	attacked = true;
	Unit* u;
	if((u = (Unit*)c->objectAtLayer(layer)) && u->isEnemy(*this))
	{
		u->health -= calculateDamage(*this, *u);
		if(u->health < 0)
			getMap()->destroyGameObject(u);
	}
}

void Unit::ambush(Unit* u)
{
	bombard(u->getCell());
}

void Unit::capture(Building* building)
{
	attacked = true;
	building->health -= 5 * atk;
	if(building->health <= 0)
	{
		//Reset the building's health and change the building's player ID
		building->setOwner(getOwner());
		building->health = building->maxHealth;
	}
}

void Unit::promote(int id)
{
	//TODO: WRITE PROMOTE METHOD
	if(id < InformationStorage::unitTypes.size())
		container->replaceGameObject(*InformationStorage::getUnit(id));
}

int Unit::calculateDamage(Unit & attacker, Unit & defender)
{
	return max(1, attacker.atk - defender.defense);
}

int Unit::calculateDamage(Unit & attacker, Building & building)
{
	return attacker.atk;
}

vector<shared_ptr<CellPathNode>> Unit::cellsCanTravelTo()
{
	vector<shared_ptr<CellPathNode>> result;
	if(container)
	{
		result = container->owner->reachableCells(container, movement, UnitTraversalHelper(this, &Unit::movementTraverse));
	}
	return result;
}

vector<shared_ptr<CellPathNode>> Unit::cellsCanHit()
{
	vector<shared_ptr<CellPathNode>> result;
	if(container)
	{
		result = container->owner->reachableCells(container, maxRange, UnitTraversalHelper(this, &Unit::attackTraverse));
		result.erase(
			remove_if(result.begin(), result.end(), 
			[&](shared_ptr<CellPathNode> c) -> bool { int dist = abs(c->cell->x - this->container->x) + abs(c->cell->y - this->container->y); return dist < minRange;}), result.end());

	}
	return result;
}

vector<Cell*> Unit::cellsCanAmbush(int dir)
{
	int AMBUSH_RANGE = 3;	

	Cell* centerLine = getMap()->neighbor(container, dir);

	vector<Cell*> result;
	int wingDir = 0;

	for(int i = 0; i < AMBUSH_RANGE && centerLine; ++i)
	{
		result.push_back(centerLine);
		
		wingDir = (dir + 1) % MovementDirection::Count;
		Cell* wingCell = getMap()->neighbor(centerLine, wingDir);
		for(int j = 0; j < i && wingCell; ++j)
		{
			result.push_back(wingCell);
			wingCell = getMap()->neighbor(wingCell, wingDir);
		}

		wingDir = (wingDir + MovementDirection::Count / 2) % MovementDirection::Count;
		wingCell = getMap()->neighbor(centerLine, wingDir);
		for(int j = 0; j < i && wingCell; ++j)
		{
			result.push_back(wingCell);
			wingCell = getMap()->neighbor(wingCell, wingDir);
		}
		centerLine = getMap()->neighbor(centerLine, dir);
	}

	return result;
}

int Unit::movementTraverse(Cell* from, Cell* to)
{
	// If there's a visible enemy unit, return a large int.
	Unit* enemy;
	if((enemy = (Unit*)to->objectAtLayer(CellLayers::Unit)) && enemy->isEnemy(*this) && enemy->visibleTo(*owner))
		return 5000;

	Terrain* t;
	// Avoid holes in the world, though there really never should be. This is just preferable to crashing.
	if(!(t = (Terrain*)to->objectAtLayer(CellLayers::Terrain)))
		return 5000;

	// Otherwise return the cost of moving across based on movementtype
	return t->movementCosts[this->movementType];
}

int Unit::attackTraverse(Cell* from, Cell* to)
{
	return 1;
}

void Unit::giveInfo(vector<string>* infoCache)
{
	infoCache->push_back("Unit");
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

void Unit::giveRobustInfo(vector<string>* infoCache)
{
	giveInfo(infoCache);
	infoCache->push_back(description);
	string s = "Cost: ";
	s += cost;
	s += " glory";
	infoCache->push_back(s);

	if(ambushes)
		infoCache->push_back("Can Ambush");
	if(bombards)
		infoCache->push_back("Can Bombard squares");
	if(captures)
		infoCache->push_back("Can Capture Buildings");
	
}


// *********************************** UnitTraversalHelper Methods **********************************
int UnitTraversalHelper::cost(Cell* from, Cell* to)
{
	return (*attachedUnit.*function)(from, to);
}

UnitTraversalHelper::UnitTraversalHelper(Unit* inAttached, UCostFunc inFunc)
{
	attachedUnit = inAttached;
	function = inFunc;
}