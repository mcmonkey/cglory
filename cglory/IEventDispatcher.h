#pragma once
template<class T, class K>
class IEventDispatcher
{
public:
	virtual void addEventListener(T&) = 0;
	virtual void removeEventListener(T&) = 0;
};

