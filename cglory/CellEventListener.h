#pragma once
#include "GameObject.h"

class GameObject;
// Interface for anthing that wants to listen for cell events.
// The only one of which is currently an object being placed.
// Actually, based on design, this should be the only method.
class CellEventListener
{
public:
	virtual void objectPlaced(GameObject* g) = 0;
};

