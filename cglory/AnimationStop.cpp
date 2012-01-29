#include "StdAfx.h"
#include "AnimationStop.h"


AnimationStop::AnimationStop(void)
{
}


AnimationStop::~AnimationStop(void)
{
}

bool AnimationStop::catchKey(KeyState k)
{
	return true;
}

bool AnimationStop::isReady()
{
	return ready;
}

void AnimationStop::gainFocus()
{

}