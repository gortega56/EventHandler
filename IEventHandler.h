#pragma once
#include <functional>
#include <unordered_map>
#include <set>
#include <stdint.h>

class IEvent
{
public:
	IEvent() {};
	virtual ~IEvent() = 0 {};
};

class IObserver
{
public:
	IObserver() {};
	~IObserver() {};

	virtual void HandleEvent(const IEvent& iEvent) = 0;
};

namespace std
{
	template<>
	struct hash<IObserver>
	{
		size_t operator()(const IObserver& observer) const
		{
			return (size_t)&observer;
		}
	};

	template<>
	struct equal_to<IObserver>
	{
		bool operator()(const IObserver& lhs, const IObserver& rhs) const
		{
			return (&lhs == &rhs);
		}
	};
}

typedef std::set<IObserver*>						ObserverSet;
typedef std::unordered_map<uint32_t, ObserverSet>	ObserverMap;

class IEventHandler
{
public:
	IEventHandler();
	~IEventHandler();

	void RegisterObserver(uint32_t eventID, IObserver* observer);
	void UnregisterObserver(uint32_t eventID, IObserver* observer);
	virtual void NotifyObservers(uint32_t eventID) = 0;

protected:
	ObserverMap mObservers;
};