#pragma once
#include "IObserver.h"
#include <set>
#include <unordered_map>
#include <functional>

class IObserver;

typedef std::set<IObserver*>		ObserverSet;
typedef std::unordered_map<const char*, ObserverSet>					ObserverMap;

class IEventHandler
{
public:
	IEventHandler();
	~IEventHandler();

	void RegisterObserver(const char* eventName, IObserver* observer);
	void UnregisterObserver(const char* eventName, IObserver* observer);
	void NotifyObservers(const char** eventNames, const int& numEvents);

protected:
	ObserverMap mObservers;
};

