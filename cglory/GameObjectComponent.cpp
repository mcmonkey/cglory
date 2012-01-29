#include "StdAfx.h"
#include "GameObjectComponent.h"

using namespace cglory::game;


GameObjectComponent::~GameObjectComponent(void)
{
}

void* GameObjectComponent::getComponent(int id)
{
	if(m_gameObject != NULL)
	{
		return m_gameObject->getComponent(id);
	}
	return NULL;
}
