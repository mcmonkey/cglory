#pragma once
#include "IGameObject.h"

namespace cglory 
{
	namespace game 
	{
		template<int ID>
		class IGameObjectComponent
		{
		public:
			static int const id = ID;
			
			template<class T>
			bool findComponent(T** outComponent) 
			{
				return (outComponent* = (T*)getComponent(T::id)) != null;	
			}
			
		protected:
			virtual void* getComponent(int id) = 0;

		};
	}
}
