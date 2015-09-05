#pragma once
#include <functional>

class IObserver
{
public:
	IObserver();
	~IObserver();

	virtual void HandleEvent(const char* eventName) = 0;
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

