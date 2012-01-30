#pragma once
template<T>
class IEventListener
{
public:
	virtual void onEvent(T &) = 0;
};

