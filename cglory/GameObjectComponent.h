#pragma once
#include "IGameObject.h"

namespace cglory 
{
	namespace game 
	{
		class GameObjectComponent : public IGameObject
		{
		protected:
			IGameObject* m_gameObject;
		public:
			GameObjectComponent(IGameObject& inObject): m_gameObject(&inObject){};
			~GameObjectComponent();
			void* getComponent(int id);
		};
	}
}