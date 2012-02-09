#pragma once
#include "IGameObject.h"


class IComponent
{

public:
	template<class T>
	bool findComponent(T** outComponent) 
	{
		return findComponent(T::id, outComponent);
	}
	virtual bool findComponent(int id, void** outcomponent);
};

namespace cglory 
{
	namespace game 
	{

		template<int ID>
		class IComponentTemplate :
			public IComponent
		{
		public:
			static int const id = ID;

		};
	}
}
