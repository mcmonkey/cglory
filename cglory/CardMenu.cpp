#include "StdAfx.h"
#include "CardMenu.h"
#include "Utility.h"
#include "CardCursor.h"


CardMenu::CardMenu(void)
{
}

CardMenu::CardMenu(Cell* c) : UIMenu(c)
{
	sendRobust = false;
	generalInit();
}

void CardMenu::generalInit()
{

	//set up the cursor for the menu like we did for pretty much every other gameSprite
	int tileSize = Stats::getTilesize();
	Utility::spriteFactory(&mCursor, L"menuCursor.png");
	mCursor.hasAnimation = true;
	mCursor.position = D3DXVECTOR3(0.0f*tileSize, 0.0f*tileSize, 10);
	mCursor.texCoord.x = 1.0f/(mCursor.originalSize.x/tileSize) * 1;
	mCursor.texCoord.y = (1.0f/(mCursor.originalSize.y/tileSize)-1) * 1;
	mCursor.drawSize = D3DXVECTOR2((float)20, (float)20);
	mCursor.sprite->TexSize.x = 1.0f/(mCursor.originalSize.x/tileSize);
	mCursor.sprite->TexSize.y = 1.0f/(mCursor.originalSize.y/tileSize);
	//mCursor.scale.x = 20.0/32.0;
	//mCursor.scale.y = 20.0/32.0;

	mCursor.position.z = ZOrdering::DeveloperConsole;

	//set these to 0 to start
	optionSelection = 0;
	options = 0;

	//load the bg for the menu
	Utility::spriteFactory(&bg, L"cardbg.png");
	bg.position.z = ZOrdering::DeveloperConsole;
	//set the width and height
	bg.scale.x = Stats::getScreenSize().x / bg.originalSize.x;
	bg.scale.y = 150 / bg.originalSize.y;
	bg.position.x = 0.0f;
	bg.position.y = Stats::getScreenSize().y/2 - bg.scale.y * bg.originalSize.y/2;

	//setup a sprite that will show where the cursor was, but without the cursor
	Utility::spriteFactory(&selected, L"selected.png");
	selected.position = D3DXVECTOR3(prevLoc.x, prevLoc.y, ZOrdering::MapOverlay);

	//setup the cards
	drawHand();
	setupCards();
	setupOptions();
	moveSelection(0,0);
	
	

	//make sure this is added to the manager
	InputManager::registerCatcher(this);
}

void CardMenu::gainFocus()
{
	while(PlayManager::getActivePlayer()->hand.size() < 5)
	{
		PlayManager::getActivePlayer()->drawCard();
		vector<Card*> s = PlayManager::getActivePlayer()->hand;
		addOption(Utility::widen(PlayManager::getActivePlayer()->hand.at(PlayManager::getActivePlayer()->hand.size()-1)->name), PlayManager::getActivePlayer()->hand.size()-1);
	}
	optionSelection = 0;
	moveSelection(0,0);
}


CardMenu::~CardMenu(void)
{
}

void CardMenu::drawHand()
{
	while(PlayManager::getActivePlayer()->hand.size() < 5)
	{
		PlayManager::getActivePlayer()->drawCard();
	}
}

void CardMenu::setupCards()
{
	for(int i=0; i<PlayManager::getActivePlayer()->hand.size(); i++)
	{
		GameSprite newCard;
		Utility::spriteFactory(&newCard, L"card.png");
		newCard.drawSize.x = 90;
		newCard.drawSize.y = 100;
		newCard.position.y = bg.position.y + 20;
		newCard.position.x = bg.position.x + i*(newCard.drawSize.x + 30) + 10;
		cards.push_back(newCard);
	}
}

void CardMenu::setupOptions()
{

	for(int i=0; i<PlayManager::getActivePlayer()->hand.size(); i++)
	{
		addOption(Utility::widen(PlayManager::getActivePlayer()->hand.at(i)->name), i);
	}
}

void CardMenu::select(int selectedId)
{
	//use dat card!
	if(PlayManager::getActivePlayer()->hand.at(selectedId))
	{
		new CardCursor(currCell, selectedId);
	}

}

void CardMenu::moveSelection(int x, int y)
{
	//move the optionSelection in the direction of the x
	optionSelection += x;
	options = cards.size();
	if(optionSelection < 0 || optionSelection >=options)
	{
		//to get optionSelection within the correct bounds, we can add to it the product of the number of options time the opposite of optionSelection's sign
		optionSelection += options*optionSelection/ fabs((double)optionSelection)*-1;
	}
	//then change the mCursor's position to match accordingly
	mCursor.position.x = cards.at(optionSelection).position.x - 10;
	mCursor.position.y = cards.at(optionSelection).position.y + cards.at(optionSelection).drawSize.y/2;

	//update the infotab
	updateInfoTab(sendRobust=false);
}

void CardMenu::updateInfoTab(bool robust)
{
	vector<string> info = vector<string>();
	info.push_back(PlayManager::getActivePlayer()->hand.at(optionSelection)->name);
	string s = "Glory: ";
	char num[64];
	itoa(PlayManager::getActivePlayer()->hand.at(optionSelection)->playCost, num, 10);
	s.append(num);
	info.push_back(s);
	if(robust)
		info.push_back(PlayManager::getActivePlayer()->hand.at(optionSelection)->description);
	PlayManager::info->updateWithCardInfo(info, robust);
	PlayManager::info->checkResize();
}

void CardMenu::draw()
{
	
	//addToDrawAbs(selected);
	addToDrawAbs(bg);
	
	for(int i = 0; i < cards.size(); i++)
	{
		addToDrawAbs(cards.at(i));
	}
	addToDrawAbs(mCursor);
}

bool CardMenu::catchKey(KeyState key)
{
	//overriding InputCatcher::catchKey to serve functionality here
	switch(key.keyCode)
	{
		case KeyCodes::DOWN:
			 return true;
		case KeyCodes::UP:
			 return true;
		case KeyCodes::LEFT:
			moveSelection(-1,  0); return true;
		case KeyCodes::RIGHT:
			moveSelection(1, 0); return true;
		case KeyCodes::ENTER:
			selectable[optionSelection] ? select(optionSelection) : 0/*play annoying sound*/ ;	   return true;
		case KeyCodes::BACKSPACE:
			InputManager::removeCatcher(); return true;
		case KeyCodes::CTRL:
			return true;
		case KeyCodes::SHIFT:
			updateInfoTab(sendRobust = !sendRobust); return true;
	}
	return false;
}


