#pragma once
#include <set>

template<class T, class K>
class EventDispatcher
{
private:
	std::set<T*> m_eventListeners;
	bool m_dispatching;

protected:
	void dispatchEvent(K& data)
	{
		auto it = m_eventListeners.begin();
		for(; it != m_eventListeners.end(); it++)
		{
			*it->onEvent(data);
		}
	};
public:
	void addEventListener(T& listener)
	{
		eventListeners.insert(&listener);
	};

	void removeEventListener(T& listener)
	{
		eventListeners.erase(listener);
	};
};

