#pragma once
#include "AnimationStop.h"
#include "GameSprite.h"

class CellLerpAnimation : public AnimationStop
{
protected:
	GameSprite* beingMoved;
	D3DXVECTOR3 from;
	D3DXVECTOR3 to;
	D3DXVECTOR3 dif;
	float		timeElapsed;
	float		finalTime;

public:
	void update();
	void draw();

	// Moves objects sprite at the given speed(px/s)
	CellLerpAnimation(GameSprite* obj, D3DXVECTOR3 from, D3DXVECTOR3 to, float speed);
	~CellLerpAnimation(void);
};

