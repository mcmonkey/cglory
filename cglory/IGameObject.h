#pragma once

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

			virtual void* getComponent(int id) = 0;
		};
	}
}
