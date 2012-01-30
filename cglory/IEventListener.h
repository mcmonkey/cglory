#pragma once
template<class T>
class IEventListener
{
public:
	virtual void onEvent(T &,  IEventDispatcher<IEventListener<T>> & source) = 0;
};

