#include "IEventHandler.h"

IEventHandler::IEventHandler()
{
}


IEventHandler::~IEventHandler()
{
	mObservers.clear();
}

void IEventHandler::RegisterObserver(uint32_t eventName, IObserver* observer)
{
	ObserverMap::iterator mapEntry = mObservers.find(eventName);
	if (mapEntry == mObservers.end()) 
	{
		// There are no observers for this event. Insert observer into set. Insert set into map.
		mObservers.insert({ eventName, ObserverSet({observer}) });
	}
	else if (mapEntry->second.find(observer) == mapEntry->second.end())
	{
		// There are observers for this event. Check for unique observer.
		mapEntry->second.insert(observer);
	}
}

void IEventHandler::UnregisterObserver(uint32_t eventName, IObserver* observer)
{
	ObserverMap::iterator mapEntry = mObservers.find(eventName);
	if (mapEntry != mObservers.end()) 
	{
		mapEntry->second.erase(observer);
		if (mapEntry->second.empty())
		{
			mObservers.erase(eventName);
		}
	}
}

void IEventHandler::NotifyObservers(uint32_t eventName)
{
	ObserverMap::iterator mapEntry = mObservers.find(eventName);
	if (mapEntry == mObservers.end())
	{
		return;
	}

	for (ObserverSet::const_iterator iter = mapEntry->second.begin(); iter != mapEntry->second.end(); iter++)
	{
		DispatchEvent(*iter);
	}
}
