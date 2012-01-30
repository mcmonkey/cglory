#include "StdAfx.h"
#include "ComponentFactory.h"
#include "ProductionComponent.h"

using namespace cglory::game;


void* ComponentFactory::createComponent(int id, IGameObject & owner)
{
	void * result = NULL;
	switch(id) 
	{
		case ProductionComponent::id:
			//result = new ProductionComponent(owner);
			break;
		default:
			result = NULL;
			break;
	}
	return result;
}