#include "EventSystem.h"

void EventSystem::AddObserver(const id_t& id, Observer* observer, EventHandler eventHandler)
{
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eventHandler = eventHandler;
	
	m_dispatchers[id].push_back(dispatcher);
}

void EventSystem::Notify(const Event& event)
{
	auto iter = m_dispatchers.find(event.id);
	if (iter != m_dispatchers.end())
	{
		//get list of dispatchers
		auto dispatchers = iter->second; //keyvalue pair. first is key, second is value, you can choose to get either
		for (auto dispatcher : dispatchers)
		{
			dispatcher.eventHandler(event);
		}
	}
}
