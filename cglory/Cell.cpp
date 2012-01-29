#include "StdAfx.h"
#include "Cell.h"
#include "PlayManager.h"

Cell::Cell(void)
{
	layers = vector<GameObject*>(CellLayers::Count, 0x0);
	cNode		= NULL;
	visibilityOverrides = 0x0;
	visibilities = vector<int>(32, 0);// Initializes it to 32 ints all at 0
}

Cell::~Cell(void)
{
	while(layers.size() > 0)
	{
		GameObject* g = layers.back();
		layers.pop_back();
		if(g)
			delete g;
	}
}

void Cell::draw()
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers[i] && layers[i]->visibleTo(*PlayManager::getActivePlayer()))
			layers[i]->draw();
	}
	
	if(!visibleTo(*PlayManager::getActivePlayer()))
	{
		GameSprite fog = SpriteHelper::fogOfWar;
		fog.position.x = position.x;
		fog.position.y = position.y;
		fog.position.z = ZOrdering::Fog;
		addToDraw(fog);
	}
}

void Cell::update()
{
	Player* p = PlayManager::getActivePlayer();
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers[i])
			layers[i]->update();
	}
}


bool Cell::visibleTo(Player const & p)
{
	return p.idMask & visibilityOverrides || visibilities[p.id] > 0;
}

void Cell::hideFrom(Player const & p)
{
	visibilityOverrides = visibilityOverrides & ~p.idMask;
}

void Cell::showTo(Player const & p)
{
	visibilityOverrides = visibilityOverrides | p.idMask;
}

void Cell::addSight(Player const & p)
{
	visibilities[p.id]++;
}

void Cell::removeSight(Player const & p)
{
	visibilities[p.id]--;
}

int Cell::totalDefense()
{
	int result = 0;
	for(int i = 0; i < layers.size(); i++)
	{
		result += layers[i]?layers[i]->defense : 0;
	}
	return result;
}

void Cell::setPosition(int inX, int inY)
{
	x = inX;
	y = inY;
	position.x = x * Stats::getTilesize();
	position.y = y * Stats::getTilesize();
}

bool Cell::addGameObject(GameObject & g)
{

	if(!validLayer(g.layer))	// G has a bad layer.
		return false;
	if(g.isIn(this))			// G is already here (returns true)
		return true;
	if(layers[g.layer])		// Something else is already here.
		return false;
	
	return replaceGameObject(g);
}

bool Cell::removeGameObject(GameObject & g)
{
	if(!validLayer(g.layer))	// This isn't at a valid layer.
		return false;
	if(layers[g.layer] != &g)	// g isn't there yo.		
		return false;
	return removeGameObject(g.layer);
}

bool Cell::replaceGameObject(GameObject & g)
{
	if(!validLayer(g.layer))	// Layer is invalid
		return false;
	
	removeGameObject(g.layer);

	layers[g.layer] = &g;
	g.setCell(this);
	notifyListeners(&g);

	return true;
}

bool Cell::removeGameObject(int layer)
{
	if(!validLayer(layer))
		return false;
	layers[layer] = 0x0;
	return true;
}

void Cell::registerListener(CellEventListener* c)
{
	listeners.emplace(c);
}

void Cell::removeListener(CellEventListener* c)
{
	auto r = listeners.find(c);
	if(r != listeners.end())
		listeners.erase(r);
}

void Cell::notifyListeners(GameObject* g)
{
	for(auto i = listeners.begin(); i != listeners.end(); ++i)
	{
		(*i)->objectPlaced(g);
	}
}

GameObject* Cell::objectAtLayer(int layer)
{
	if(validLayer(layer))
		return layers[layer];
	return 0x0;
}

GameObject* Cell::top()
{
	for(int i = (int)layers.size() - 1; i > -1; i++)
		if(layers[i])
			return layers[i];
	return 0;
}

bool Cell::validLayer(int layer)
{
	return layer >= 0 && layer < layers.size();
}