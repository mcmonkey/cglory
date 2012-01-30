#pragma once
#include "IProductionComponent.h"
#include "GameObjectComponent.h"
#include <vector>

namespace cglory 
{
	namespace game 
	{
		class ProductionComponent : 
			public IProductionComponent, GameObjectComponent
		{
		public:
			bool canProduceAt(int id, int x, int y);
			bool canProduceAt(int id, IGameObject &);
			bool canProduceAtThis(int id);

			bool produceAt(int id, int x, int y);
			bool produceAt(int id, IGameObject &);
			bool produceAtThis(int id);

			std::vector<int>* getAvailableProduction();

			ProductionComponent(IGameObject & owner) : GameObjectComponent(owner){};
			~ProductionComponent(void);
		};
	}
}