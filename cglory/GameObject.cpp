#include "StdAfx.h"
#include "GameObject.h"

using namespace cglory::game;
using cglory::game::GameObject;

GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

bool GameObject::addComponent(int id, void* component)
{
	auto result = components.find(id);
	if(result != components.end())
	{
		components[id] = component;
		return false;
	}
	return true;
}



