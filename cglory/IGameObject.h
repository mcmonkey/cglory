#pragma once
#include "IGameObjectComponent.h"
namespace cglory 
{
	namespace game 
	{
		class IGameObject :
			public IGameObjectComponent<0>
		{
		public:
			template<class T>
			bool addComponent(T & component)
			{
				return addComponent(T::id, (void*)&T);
			}

			template<class T>
			bool replaceComponent(T & component)
			{
				removeComponent();
				return addCopmonent(component);
			}

			template<class T>
			bool removeComponent()
			{
				return removeComponent(t::id);
			}

			template<class T>
			bool addAndFindComponent(T** outComponent)
			{
				if(addComponent(T::id))
				{
					return (T*)getComponent(T::id);
				}
				return NULL;
			}
		protected:
			virtual bool addComponent(int id, void* component) = 0;
			virtual bool removeComponent(int id) = 0;
		};
	}
}
