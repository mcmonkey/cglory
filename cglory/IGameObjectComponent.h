#pragma once
#include "GameObject.h"

namespace cglory 
{
	namespace game 
	{
		template<int ID>
		class IGameObjectComponent :
			public IGameObject
		{
		public:
			static int const id = ID;
		};
	}
}
