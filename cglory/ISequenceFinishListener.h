#pragma once
#include "IEventListener.h"
#include "ISequence.h"

class ISequenceFinishListener :
	public IEventlistener<ISequence>
{
public:
	virtual void onEvent(int*) = 0;
};

