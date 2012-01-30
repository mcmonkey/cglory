#pragma once
#include "IGameObject.h"

class ComponentFactory
{
public:
	template<class T>
	static T & createComponent(cglory::game::IGameObject & owner)
	{
		return (T*)createComponent(T::id, owner);
	}

	static void* createComponent(int id, cglory::game::IGameObject & owner);
};

