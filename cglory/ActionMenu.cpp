#include "StdAfx.h"
#include "ActionMenu.h"


void ActionMenu::generalInit()
{
	//set up the cursor for the menu like we did for pretty much every other gameSprite
	int tileSize = Stats::getTilesize();
	Utility::spriteFactory(&mCursor, L"menuCursor.png");
	mCursor.hasAnimation = true;
	mCursor.position = D3DXVECTOR3(0.0f*tileSize, 0.0f*tileSize, 10);
	mCursor.texCoord.x = 1.0f/(mCursor.originalSize.x/tileSize) * 1;
	mCursor.texCoord.y = (1.0f/(mCursor.originalSize.y/tileSize)-1) * 1;
	mCursor.drawSize = D3DXVECTOR2((float)tileSize, (float)tileSize);
	mCursor.sprite->TexSize.x = 1.0f/(mCursor.originalSize.x/tileSize);
	mCursor.sprite->TexSize.y = 1.0f/(mCursor.originalSize.y/tileSize);
	mCursor.name = "mCursor";
	mCursor.position.z = ZOrdering::DeveloperConsole;

	//set these to 0 to start
	optionSelection = 0;
	options = 0;

	//load the bg for the menu
	Utility::spriteFactory(&bg, L"consolebg.png");
	bg.position.z = ZOrdering::DeveloperConsole;
	//set the width. The length is determined by the amount of options
	bg.scale.x = 100;

	//construct the font object
	menuOptionHeight = 20;
	Utility::fontFactory(menuOptionHeight, L"Consolas", &consoleFont);
	

	Utility::spriteFactory(&available, L"available.png");
	
	

	//make sure this is added to the manager
	InputManager::registerCatcher(this);
	//MenuManager::addMenu(this);
}
ActionMenu::ActionMenu(void)
{
	//default constructor
	//This should be rarely called
	unit = NULL;
	build = NULL;

	generalInit();

	bg.scale.y = 60;

}

ActionMenu::ActionMenu(int mType, void* p)
{
	//set the menu type
	menuType = mType;

	//set the possible unit and building pointers to null
	unit = NULL;
	build = NULL;

	//call the general initialization
	generalInit();

	switch(menuType)
	{
	case MenuType::UnitOptions:
		//if the menu type tells us that this menu is for a unit, then cast the void pointer as such
		unit = (Unit*) p;

		//add names for each option and increment for each one
		optionNames.push_back(L"Move");
		options++;

		optionNames.push_back(L"Attack");
		options++;

		optionNames.push_back(L"Exit");
		options++;

		//setup the space for the text drawing
		bg.scale.y = menuOptionHeight*options;
		drawSpace.left = unit->getCell()->position.x +16 - Utility::camera->x;
		drawSpace.right = drawSpace.left + bg.scale.x*2;
		drawSpace.top = unit->getCell()->position.y +16 - Utility::camera->y;
		drawSpace.bottom = drawSpace.top + bg.scale.y*2;
		break;
	case MenuType::BuildingOptions:
		//due to the switch, we know this should be a building
		build = (Building*) p;

		//set up the options
		optionNames.push_back(L"Build");
		options++;

		optionNames.push_back(L"Exit");
		options++;

		//setup the space for the text drawing
		bg.scale.y = menuOptionHeight*options;
		drawSpace.left = build->gSprite.position.x +16 - Utility::camera->x;
		drawSpace.right = drawSpace.left + bg.scale.x*2;
		drawSpace.top = build->gSprite.position.y +16 - Utility::camera->y;
		drawSpace.bottom = drawSpace.top + bg.scale.y*2;
		break;
	case MenuType::BuildingProductionOptions:
		//this too should have a building, but this is a sub menu. it is called from within a BuildingOptions typed ActionMenu
		build = (Building*) p;

		//set up the options
		//the options in this case come from what the building can build
		UnitInfo uI;
		for(int i = 0; i < build->availableProduction.size(); i++)
		{
			uI = InformationStorage::unitTypes[(build->availableProduction.at(i))];
			optionNames.push_back((LPCWSTR)Utility::widen(uI.name.c_str()).c_str());
			options++;
		}
		optionNames.push_back(L"Exit");
		options++;

		//setup the space for the text drawing
		bg.scale.y = menuOptionHeight*options;
		drawSpace.left = build->gSprite.position.x +32 - Utility::camera->x;
		drawSpace.right = drawSpace.left + bg.scale.x*2;
		drawSpace.top = build->gSprite.position.y +16 - Utility::camera->y;
		drawSpace.bottom = drawSpace.top + bg.scale.y*2;
		break;
	}
	//set the y-scale since now we know how many options are available
	
	
	//let the positions of the bg and the cursor based on the drawSpace
	bg.position.x = drawSpace.left +Utility::camera->x;
	bg.position.y = drawSpace.top +Utility::camera->y;
	mCursor.position.x = drawSpace.left +Utility::camera->x;
	mCursor.position.y = drawSpace.top- menuOptionHeight/2 +Utility::camera->y;
}


ActionMenu::~ActionMenu(void)
{
}


bool ActionMenu::catchKey(KeyState key)
{
	//overriding InputCatcher::catchKey to serve functionality here
	switch(key.keyCode)
	{
		case KeyCodes::DOWN:
			moveSelection(0,  1); return true;
		case KeyCodes::UP:
			moveSelection(0, -1); return true;
		case KeyCodes::LEFT:
			return true;
		case KeyCodes::RIGHT:
			return true;
		case KeyCodes::ENTER:
			select();		   return true;
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
	}
	return false;
}

void ActionMenu::select()
{
	//based on how this was initialized and what state the game is in, the options and thus the results will be different
	//this switch will take care of figuring out what the menu was created for and thus respond to the caught option accordingly
	//when new input catchers are added here, the game state may (and likely will) change or attempt to change.
	GameCursor* sC;
	switch(menuType)
	{
	case MenuType::UnitOptions:
		switch(optionSelection)
		{
		case 0:
			//Move
			//create another cursor that will move around to select a spot to move to
			sC = new SelectionCursor(unit);
			
			Utility::setState(GameState::MovementSelect);
			return;
			break;
		case 1:
			//Attack
			//add another cursor that can select an enemy to hit
			sC = new AttackCursor(unit);
			return;
			break;
		case 2:
			//Exit
			break;
		}
		break;
	case MenuType::BuildingOptions:
		switch(optionSelection)
		{
		case 0:
			//build
			Utility::setState(GameState::InMenu);
			new ActionMenu(MenuType::BuildingProductionOptions, build);
			return ;
			break;
		case 1:
			//Exit
			break;
		}
		break;
	case MenuType::BuildingProductionOptions:
		if(optionSelection != optionNames.size() -1)
		{
			//if the optionSelection isn't the last one in the list, then the player tried to build a unit
			build->produce(optionSelection);
		}
		break;
	}

	//if we've gotten here, then that means this menu has completed its function and can be removed
	//there are times when this menu will open another menu and should remain underneath. these options will return before this line is 
	//	reached and the menu above will work on removing menus underneath should that be neccesary
	InputManager::removeCatcher();
	//MenuManager::removeMenu();
}

void ActionMenu::moveSelection(int x, int y)
{
	//move the optionSelection in the direction of the y
	optionSelection += y;
	if(optionSelection < 0 || optionSelection >=options)
	{
		//to get optionSelection within the correct bounds, we can add to it the product of the number of options time the opposite of optionSelection's sign
		optionSelection += options*optionSelection/ fabs((double)optionSelection)*-1;
	}
	//then change the mCursor's position to match accordingly
	mCursor.position.y = (optionSelection*menuOptionHeight) + drawSpace.top - menuOptionHeight/2;
}

void ActionMenu::draw()
{
	//add the background and the cursor to draw
	addToDraw(bg);
	addToDraw(mCursor);

	//then, for each optionName, we should draw text for it
	RECT tempDrawSpace = drawSpace;
	for(int i=0; i<optionNames.size(); i++)
	{
		tempDrawSpace.top += consoleFont->DrawTextW(0, optionNames.at(i).c_str(), -1, &tempDrawSpace, DT_NOCLIP | DT_SINGLELINE, D3DXCOLOR(1,1,1,1));
	}
	
}