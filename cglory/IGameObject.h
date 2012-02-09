#pragma once
#include "IUnknown.h"

namespace cglory 
{
	namespace game 
	{
		// Note, the components in this class are not quite the same as the normal IComponent.
		class IGameObject :
			public IUnknownTemplate<1>
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
					return findComponent(outComponent);
				}
				return false;
			}

			template<class T>
			bool findComponent(T** outComponent)
			{
				return findComponent(T::id, outComponent);
			}

		protected:
			virtual bool addComponent(int id, void* component) = 0;
			virtual bool removeComponent(int id) = 0;
			virtual bool findComponent(int id, void**) = 0;

		};
	}
}
