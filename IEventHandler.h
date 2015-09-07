#pragma once
#include "IObserver.h"
#include <set>
#include <unordered_map>
#include <stdint.h>

class IObserver;

typedef std::set<IObserver*>						ObserverSet;
typedef std::unordered_map<uint32_t, ObserverSet>	ObserverMap;

class IEventHandler
{
public:
	IEventHandler();
	~IEventHandler();

	void RegisterObserver(uint32_t eventName, IObserver* observer);
	void UnregisterObserver(uint32_t eventName, IObserver* observer);
	void NotifyObservers(uint32_t eventName);

protected:
	ObserverMap mObservers;
};

