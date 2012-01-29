#include "StdAfx.h"
#include "PlayerOwned.h"
#include "Cell.h"
#include "Map.h"

void PlayerOwned::setCell(Cell* c)
{
	GameObject::setCell(c);
	reevaluateVisibleCells();
}

Player* PlayerOwned::getOwner()
{
	return owner;
}

bool PlayerOwned::isEnemy(PlayerOwned & other)
{
	if(!other.getOwner() || !getOwner())
		return true;
	return other.getOwner()->isEnemy(*getOwner());
}


// Sets the player to p. Accepts NULL(0) as a way to remove this unit from the owner's roster.
void PlayerOwned::setOwner(Player* p)
{
	if(owner)
	{
		blind();					// Removes old sight from old player.
		owner->releaseObject(this);
	}
	owner = p;
	grantVision();					// Adds sight for the new player.
}

// -_-
void PlayerOwned::reevaluateVisibleCells()
{
	blind();
	grantVision();
}

// Hides all cells from this unit.
// Multiple calls do nothing, as the visible cells vector is cleared.
void PlayerOwned::blind()
{
	if(sightCanChange)
	{
		for(auto i = visibleCells.begin(); i < visibleCells.end(); i++)
		{
			(*i)->cell->removeSight(*owner);
		}
		visibleCells.clear();
	}
}

// Reveals all the cells from this unit.
// Fails if no cell or player is set.
// Multiple do nothing.
void PlayerOwned::grantVision()
{
	if(container && owner && visibleCells.size() == 0 && sightCanChange)
	{
		visibleCells = container->owner->reachableCells(container, sightRange, POwnedTraversalHelper(this, &PlayerOwned::visibilityTraverse));
	
		for(auto i = visibleCells.begin(); i < visibleCells.end(); i++)
		{
			(*i)->cell->addSight(*owner);
		}
	}
}

void PlayerOwned::draw()
{
	gSprite.color = owner && visibleTo(*PlayManager::getActivePlayer())? owner->getColor() : D3DXCOLOR(1, 1, 1, 1);
	GameObject::draw();

	D3DXVECTOR2 absPosition = -*Utility::camera + container->position;
	RECT r = RECT();
	r.left = absPosition.x;
	r.top = absPosition.y;
	r.right = r.left + Stats::getTilesize();
	r.bottom = r.top + Stats::getTilesize();
}

void PlayerOwned::destroy()
{
	GameObject::destroy();
	setOwner(0x0);
}

PlayerOwned::PlayerOwned(void)
{
	owner = 0x0;
	sightRange = 0;
}


PlayerOwned::~PlayerOwned(void)
{
}

// *********************************** UnitTraversalHelper Methods **********************************
int POwnedTraversalHelper::cost(Cell* from, Cell* to)
{
	return (*attachedUnit.*function)(from, to);
}

POwnedTraversalHelper::POwnedTraversalHelper(PlayerOwned* inAttached, PCostFunc inFunc)
{
	attachedUnit = inAttached;
	function = inFunc;
}


// Currently line of sight is very simple.
int PlayerOwned::visibilityTraverse(Cell* from, Cell* to)
{
	return 1;
}