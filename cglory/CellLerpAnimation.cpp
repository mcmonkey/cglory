#include "StdAfx.h"
#include "CellLerpAnimation.h"


CellLerpAnimation::CellLerpAnimation(GameSprite* obj, D3DXVECTOR3 from, D3DXVECTOR3 to, float speed)
{
	ready = false;
	this->beingMoved = obj;
	
	this->from = from;
	this->to = to;
	this->dif = to - from;

	this->timeElapsed = 0.0f;
	this->finalTime = sqrt(dif.x * dif.x + dif.y * dif.y) / speed;
}

CellLerpAnimation::~CellLerpAnimation(void)
{
}

void CellLerpAnimation::update()
{
	timeElapsed += Stats::dt();
	if(timeElapsed >= finalTime)
	{
		ready = true;
		beingMoved->position = to;
	}
	else
		;
}

void CellLerpAnimation::draw()
{
	// GNDN
}