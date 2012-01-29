#pragma once
#include "GameObject.h"
#include <vector>

class TerrainInfo;

// Class that wraps around TerrainInfo. Really just needed so I could make a callable draw function.
class Terrain : public GameObject
{

//------------------------ Members -------------------------------------
public:
	vector<int>	movementCosts;
	bool		grantsCover;

//------------------------ Members -------------------------------------
public:
	GameObject* copy();
	Terrain(void);
	~Terrain(void);
	void select();	// Needs to be overriden for insantiation.
	virtual void giveInfo(vector<string>* infoCache);		//returns a short list of information about the object

	virtual void giveRobustInfo(vector<string>* infoCache);	//returns a more detailed list of information about the object
};

