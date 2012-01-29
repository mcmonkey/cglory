#include "StdAfx.h"
#include "AmbushDirectionSelector.h"
#include "InputManager.h"

AmbushDirectionSelector::AmbushDirectionSelector(Unit* u)
{
	ambusher = u;
	InputManager::registerCatcher(this);
	ambushable = ambusher->cellsCanAmbush(MovementDirection::RIGHT);
}


AmbushDirectionSelector::~AmbushDirectionSelector(void)
{
}

void AmbushDirectionSelector::gainFocus()
{

}

bool AmbushDirectionSelector::catchKey(KeyState k)
{
	switch(k.keyCode)
	{
		case KeyCodes::UP:
			ambushable = ambusher->cellsCanAmbush(MovementDirection::UP); return true;
		case KeyCodes::DOWN:
			ambushable = ambusher->cellsCanAmbush(MovementDirection::DOWN); return true;
		case KeyCodes::LEFT:
			ambushable = ambusher->cellsCanAmbush(MovementDirection::LEFT); return true;
		case KeyCodes::RIGHT:
			ambushable = ambusher->cellsCanAmbush(MovementDirection::RIGHT); return true;
		case KeyCodes::ENTER:
			ambusher->targetForAmbush(ambushable);
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
		
			
	}
}

void AmbushDirectionSelector::draw()
{
	GameSprite g = SpriteHelper::ambushOverlay;
	for(auto i = ambushable.begin(); i < ambushable.end(); ++i)
	{
		g.position = (*i)->position;
		g.position.z =  ZOrdering::MapOverlay;
		addToDraw(g);
	}
}