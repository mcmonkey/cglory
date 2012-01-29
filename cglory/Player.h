#pragma once
#include <vector>
#include <string>
#include "PlayerOwned.h"
#include "Card.h"

using namespace std;

class PlayerOwned;

class Player
{
//------------------------ Members -------------------------------------
public:
	string			name;		// Don't even worry about filling for now.
	int				glory;		// Current amount of glory the player has.
	unsigned int	id;			// An int identifying this player.
	unsigned int	idMask;		// Bit mask for identifying this player.
	vector<Card*>	deck;		//The player's deck
	vector<Card*>	hand;		//The player's current hand
	vector<Card*>	discard;	//The player's current discard pile;

	PlayerOwned*	headquarters;	// Player loses if they lose this building (though it could be set to a unit if you really wanted)

	bool			stillPlaying;
	
	
	//--767-- --777--
	//we should keep track of the cursor coords and camera coords when the player swaps. we'll need to reset the coords so that the next player can't figure out where the other player is.


private:
	vector<PlayerOwned*> objects;

//------------------------ Methods -------------------------------------
public:
	Player(int id);
	~Player(void);
	
	void getGloryFromBuildings();		
	
	void giveObject(PlayerOwned*);				// Gives a gameobject to this player. Calls it's setOwner method here.
	void releaseObject(PlayerOwned const *);	// Releases a gameobject. Does not modify the gameobject.
	
	bool hasUnits();
	void lose();

	void drawCard();							//Draws a card from that player's deck
	void discardCard();							//Discards a random card from the player's hand
	void discardCard(int index);				//Discards the card at index from the hand
	bool playCard(int index, Cell* target);		//Plays the card at index from the hand targeting the Cell target
	void purchaseCard(int index);				//Purchase a card of ID index with glory
	void addToDeck(int index);					//Add a card to the deck, used for inital deck set-up

	// Updates functions for before and after a turn.
	void preTurn();
	void postTurn();

	D3DXCOLOR	getColor();


	bool isEnemy(Player & p);					// Whether p is an enemy of this player or not. Currently, only uses equality. Later teams?				
};