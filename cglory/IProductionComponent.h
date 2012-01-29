#pragma once
#include "IGameObjectComponent.h"
#include <vector>

namespace cglory 
{
	namespace game 
	{
		class IProductionComponent : IGameObjectComponent<2>
		{
		public:
			bool produce(int id);
			std::vector<int> getAvailableProduction();
		};
	}
}