#pragma once
#include "ICGloryComponent.h"
#include <vector>

namespace cglory 
{
	namespace game 
	{
		class IProductionComponent : 
			public ICGloryComponent<2>
		{
		public:
			virtual bool canProduceAt(int id, int x, int y) = 0;
			virtual bool canProduceAt(int id, IGameObject &) = 0;
			virtual bool canProduceAtThis(int id) = 0;

			virtual bool produceAt(int id, int x, int y) = 0;
			virtual bool produceAt(int id, IGameObject &) = 0;
			virtual bool produceAtThis(int id) = 0;
			
			virtual std::vector<int>* getAvailableProduction() = 0;
		};
	}
}