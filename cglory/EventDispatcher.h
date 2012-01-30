#pragma once
#include <set>
#include "Logging.h"

template<class T, class K>
class EventDispatcher
{
private:
	std::set<T*> m_eventListeners;
	bool m_dispatching;

protected:
	void dispatchEvent(K& data)
	{
		if(m_dispatching)
		{
			ERROR(L_SECTION_EVENTS, "Cannot nest dispatches.")
		}
		else 
		{
			m_dispatching = true;
			std::set<T*> & currentListeners = m_eventListeners;
			// currentListeners = std::set<T*>(m_eventListeners);
			// Switching out the above line as a safety precaution could lead to a lot of memory churn.
			// Lets see via warnings if we can keep this case minimal, or think of a less memory churny way to do it.
			auto it = currentListeners.begin();
			for(; it != currentListeners.end(); it++)
			{
				*it->onEvent(data);
			}
			m_dispatching = false;
		}
	};
public:
	void addEventListener(T& listener)
	{
		if(m_dispatching) 
		{
			// Leaving this as a warning. If it occurs at all, I'll have to make dispatching safe.
			WARNING(L_SECTION_EVENTS, "addEventListener called during dispatch");
		}
		eventListeners.insert(&listener);
	};

	void removeEventListener(T& listener)
	{
		if(m_dispatching) 
		{
			// Leaving this as a warning. If it occurs at all, I'll have to make dispatching safe.
			WARNING(L_SECTION_EVENTS, "removeEventListener called during dispatch");
		}
		eventListeners.erase(listener);
	};

	EventDispatcher() :
		m_dispatching(false)
	{};
};

