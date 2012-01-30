#include "StdAfx.h"
#include "ProductionComponent.h"

using namespace cglory::game;


bool ProductionComponent::canProduceAt(int id, int x, int y)
{
	return false;
}

bool ProductionComponent::canProduceAt(int id, IGameObject &)
{
	return false;
}

bool ProductionComponent::canProduceAtThis(int id)
{
	return false;
}

bool ProductionComponent::produceAt(int id, int x, int y)
{
	return false;
}
bool ProductionComponent::produceAt(int id, IGameObject &)
{
	return false;
}

bool ProductionComponent::produceAtThis(int id)
{
	return false;
}

std::vector<int>* ProductionComponent::getAvailableProduction()
{
	return NULL;
}