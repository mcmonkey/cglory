#pragma once
#include "IGameObject.h"

namespace cglory 
{
	namespace game 
	{
		template<int ID, class DATA_LOADER, class DATA_SAVER>
		class IGameObjectComponent :
			public IGameObject
		{
		public:
			static int const id = ID;

			virtual void load(DATA_LOADER &) = 0;
			virtual void loadState(DATA_LOADER &) = 0;
			virtual void saveState(DATA_SAVER &) = 0;
		};
	}
}
