#include "CardEffects.h"
#ifndef CARD_HELPER
#define CARD_HELPER

//The class for tactician cards

class Card
{

	//--------------------Variables-----------------
public:
	int id;									//The card's ID as found in the info file
	std::string name;						//The card's title
	std::string description;				//The card's description
	std::vector<CardEffect*> effects;		//The different effects that will execute when this card is played
	int purchaseCost;						//The amount of glory it costs to purchase this card for a deck
	int playCost;							//The amount of glory it costs to play this card from a player's hand
	Player* owner;							//The player who owns this card.  Needed to decide who owns a building
											//or unit made by a card

	//------------------Methods----------------------
	Card();
	~Card();
	//The different execute methods take different types of objects, and are used with different types of effects
	bool execute(Building* b);
	bool execute(Unit* u);
	bool execute(Terrain* t);
	bool execute(Player* p);
	bool execute(Cell* c);
	bool execute(Unit* u, Cell* c);
	bool execute();
};
#endif