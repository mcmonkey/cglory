#include "StdAfx.h"
#include "GameObject.h"
#include "InputManager.h"

// Moves the gameobject to another cell.
void GameObject::setCell(Cell* c)
{
	if(container)
		container->removeGameObject(*this);
	container = c;
	if(container)	
	{
		gSprite.position.x = container->position.x;
		gSprite.position.y = container->position.y;
	}
}

Cell* GameObject::getCell()
{
	return container;
}

bool GameObject::isIn(Cell* c)
{
	return c == container;
}

void GameObject::destroy()
{
	setCell(0x0);
}

// GETTER: gSprite
GameSprite* GameObject::getGSprite()
{
	return &gSprite;
}

bool GameObject::visibleTo(Player & p)
{
	return true;
}

void GameObject::update()
{
	if(currentStop)
	{
		currentStop->update();
		if(currentStop->isReady())
		{
			InputManager::removeCatcher();
			currentStop = 0x0;
		}
	}
}

void GameObject::setStop(AnimationStop* as)
{
	if(currentStop)
		InputManager::removeCatcher();
	InputManager::registerCatcher(as);
	currentStop = as;
}

void GameObject::draw()
{
	addToDraw(gSprite);
}

Map* GameObject::getMap()
{
	if(container)
		return container->owner;
	return 0x0;
}

void GameObject::giveInfo(vector<string>* infoCache)
{
	
}

void GameObject::giveRobustInfo(vector<string>* infoCache)
{
	//get what normal info would give
	//and then add defense
	giveInfo(infoCache);
	char temp[255];
	itoa(defense,temp,10);
	infoCache->push_back(temp);
}

GameObject::GameObject(void)
{
	container = 0x0;
	currentStop = 0x0;
}


GameObject::~GameObject(void)
{
}

