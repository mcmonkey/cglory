#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include "tinyxml.h"

using namespace std;

class CardEffect;

// Holder class, should be created once per terrain type on startup, and stored in InformationStorage
class CardInfo
{
//------------------------ Members -------------------------------------
private:
	

public:
	int					id;
	string				name;
	string				description;
	int					purchaseCost;
	int					playCost;
	vector<CardEffect*>	effects; // Vector of card effects

//------------------------ Methods -------------------------------------
public:
	CardInfo(void);
	~CardInfo(void);
	void factory(Card* c);
	void load(TiXmlNode*);
};