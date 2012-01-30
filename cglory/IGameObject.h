#pragma once
#include <vector>

namespace cglory 
{
	namespace game 
	{
		class IGameObject
		{
		public:
			template<class T>
			bool findComponent(T** outComponent) 
			{
				return (outComponent* = (T*)getComponent(T::id)) != null;	
			}

			template<class T>
			inline T* addComponent()
			{
				return (T*)addComponent(T::id);
			}

			template<class T>
			inline bool addAndFindComponent(T** outComponent)
			{
				if(addComponent(T::id))
				{
					return (T*)getComponent(T::id);
				}
				return NULL;
			}

			virtual void* getComponent(int id) = 0;
		protected:
			virtual bool addComponent(int id) = 0;
		};
	}
}
