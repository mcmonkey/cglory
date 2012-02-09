#pragma once
#include "IGameObject.h"
#include <map>

// Base object in the game. Can be put in a Cell, draw itself, and contribute to defense of the cell.

namespace cglory 
{
	namespace game 
	{
		class GameObject :
			public IGameObject
		{
		private:
			std::map<int, void*> components;
		public:
			GameObject(void);
			~GameObject(void);

		protected:
			virtual bool	addComponent(int id, void* component);
			virtual void*	getComponent(int id);
			virtual bool	removeComponent(int id);
		};

	}
}