#pragma once
#include <functional>
#include <unordered_map>
#include <set>
#include <stdint.h>

#pragma warning (disable: 4251)

#ifdef _WINDLL
#define EVENT_API __declspec(dllexport)
#else
#define EventDispatcher __declspec(dllimport)
#endif

namespace cliqCity
{
	class EVENT_API IEvent
	{
	public:
		IEvent() {};
		virtual ~IEvent() = 0 {};
	};

	class EVENT_API IObserver
	{
	public:
		IObserver() {};
		~IObserver() {};

		virtual void HandleEvent(const IEvent& iEvent) = 0;
	};



	typedef std::set<IObserver*>						ObserverSet;
	typedef std::unordered_map<uint32_t, ObserverSet>	ObserverMap;

	class EVENT_API IEventHandler
	{
	public:
		IEventHandler();
		~IEventHandler();

		void RegisterObserver(uint32_t eventID, IObserver* observer);
		void UnregisterObserver(uint32_t eventID, IObserver* observer);
		virtual void NotifyObservers(const IEvent& iEvent) = 0;

	protected:
		ObserverMap mObservers;
	};
}

namespace std
{
	template<>
	struct EVENT_API hash<cliqCity::IObserver>
	{
		size_t operator()(const cliqCity::IObserver& observer) const
		{
			return (size_t)&observer;
		}
	};

	template<>
	struct EVENT_API equal_to<cliqCity::IObserver>
	{
		bool operator()(const cliqCity::IObserver& lhs, const cliqCity::IObserver& rhs) const
		{
			return (&lhs == &rhs);
		}
	};
}