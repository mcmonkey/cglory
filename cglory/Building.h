#pragma once
#include <vector>
#include "PlayerOwned.h"

using namespace std;

class PlayerOwned;

// Represents a building in game that can modify defense values, and produce units.
class Building : public PlayerOwned
{
//------------------------ Members -------------------------------------
public:
	vector<int> availableProduction;
	float gloryMod;
	
//------------------------ Methods -------------------------------------
public:
	GameObject* copy();
	Building(void);
	~Building(void);
	void select();
	bool produce(int id);
	void preTurn();
	void postTurn();
	virtual void giveInfo(vector<string>* infoCache);		//returns a short list of information about the object

	virtual void giveRobustInfo(vector<string>* infoCache);	//returns a more detailed list of information about the object
};

