#include "StdAfx.h"
#include "Player.h"
#include <algorithm>
#include "Sound.h"
#include "Card.h"

vector<D3DXCOLOR> colors = vector<D3DXCOLOR>();

Player::Player(int inID)
{
	id = inID;
	idMask = 1 << inID;
	objects = vector<PlayerOwned*>();
	glory = 500;
	stillPlaying = true;
	headquarters = NULL;
	
	if(colors.size() == 0)
	{
		float f = .5f;
		colors.push_back(D3DXCOLOR(1, 1, 1, 1));
		colors.push_back(D3DXCOLOR(1, f, f, 1));
		colors.push_back(D3DXCOLOR(f, 1, f, 1));
		colors.push_back(D3DXCOLOR(f, f, 1, 1));
		colors.push_back(D3DXCOLOR(1, 1, f, 1));
	}
}


Player::~Player(void)
{
}

D3DXCOLOR Player::getColor()
{
	return colors[id];
}

// Gives a unit/building/terrain to this player.
void Player::giveObject(PlayerOwned* u)
{
	u->setOwner(this);
	objects.push_back(u);
}

// Iterates through the 
void Player::releaseObject(PlayerOwned const* g)
{
	
	vector<PlayerOwned*>::iterator r = find(objects.begin(), objects.end(), g);
	if(r < objects.end())
	{
		objects.erase(r);
	}

 	if(g == headquarters)
		lose();
}

void Player::lose()
{
	stillPlaying = false;
	
	while(objects.size() > 0)
	{
		if(objects[0] == headquarters)
		{
			Cell* c = objects[0]->getCell();
			objects[0]->destroy();
			c->owner->createBuilding(0, 0, c->x, c->y);
		}
		else if(objects[0]->layer == CellLayers::Building)
		{
			objects[0]->setOwner(objects[0]->getMap()->getNeutral());
		}
		else
		{
			objects[0]->destroy();
		}
	}
	PlayManager::playerHasLost(this);
}

bool Player::isEnemy(Player & p)
{
	return p.id != id;
}

bool Player::hasUnits()
{
	for(int i=0; i<objects.size(); i++)
	{
		if(objects[i]->layer == CellLayers::Unit)
			return true;
	}
	return false;
}

void Player::preTurn()
{
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->preTurn();
	}
}

void Player::postTurn()
{
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->postTurn();
	}
}

void Player::discardCard()
{
	if(hand.size() > 0)
	{
		int i = rand()%hand.size();
		discard.push_back(hand[i]);
		hand.erase(hand.begin()+i);
	}
}

void Player::discardCard(int index)
{
	if(index < hand.size())
	{
		discard.push_back(hand[index]);
		hand.erase(hand.begin()+index);
	}
}

void Player::drawCard()
{
	if(deck.size() > 0)
	{
		hand.push_back(deck[0]);
		deck.erase(deck.begin());
	}
	else
	{
		//Shuffle the discard back into the deck. 
		while(discard.size() > 0)
		{
			int i = rand()%discard.size();
			deck.push_back(discard[i]);
			discard.erase(discard.begin()+i);
		}
		//Draw a card if there's a card in the deck
		if(deck.size() > 0)
		{
			hand.push_back(deck[0]);
			deck.erase(deck.begin());
		}
	}
}

bool Player::playCard(int index, Cell* target)
{
	bool played = false;
	if(glory >= hand.at(index)->playCost)
	{
		played = hand.at(index)->execute(target);
		if(played)
		{
			glory -= hand.at(index)->playCost;
			discardCard(index);
		}
	}
	return played;
}

void Player::purchaseCard(int index)
{
	if(index < InformationStorage::cardTypes.size() && glory >= InformationStorage::cardTypes[index].purchaseCost)
	{
		glory -= InformationStorage::cardTypes[index].purchaseCost;
		discard.push_back(InformationStorage::getCard(index));
		discard.back()->owner = this;
	}
}

void Player::addToDeck(int index)
{
	if(index < InformationStorage::cardTypes.size())
	{
		deck.push_back(InformationStorage::getCard(index));
		deck.back()->owner = this;
	}
}