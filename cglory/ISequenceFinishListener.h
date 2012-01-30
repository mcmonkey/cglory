#pragma once
#include "IEventListener.h"
#include "ISequence.h"

class ISequenceFinishListener :
	public IEventListener<ISequence>
{
public:
	virtual void onEvent(ISequence*, IEventDispatcher<ISequenceFinishListener>) = 0;
};

