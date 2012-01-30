#pragma once
#include "ISequenceFinishListener.h"
#include "IEventDispatcher.h"

class ISequence :
	public IEventDispatcher<ISequenceFinishListener, ISequence>
{
public:
	virtual void start() = 0;
	virtual bool interrupt() = 0;
};

