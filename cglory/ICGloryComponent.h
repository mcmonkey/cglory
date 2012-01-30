#pragma once
#include "IGameObjectComponent.h"
#include "tinyxml.h"

namespace cglory 
{
	namespace game 
	{
		template<int ID>
		class ICGloryComponent :
			public IGameObjectComponent<ID, TiXmlElement, int>
		{
		public:
			virtual void load(TiXmlElement &) = 0;
			virtual void loadState(TiXmlElement &) = 0;
			virtual void saveState(int &) = 0;
		};
	}
}
