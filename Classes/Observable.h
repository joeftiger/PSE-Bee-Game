//
// Created by julius on 24.03.19.
//

#ifndef PSE_BEE_GAME_OBSERVABLE_H
#define PSE_BEE_GAME_OBSERVABLE_H

#include "Observer.h"

class Observable {
private:

	/** observers having subscribed to this observable */
	std::vector<std::reference_wrapper<Observer>> _observers;

protected:
	/**
	 * Should notify all observers of a change in this observable.
	 */
	const void notifyObservers() {
		for (Observer &o : _observers) {
			o.notify(this);
		}
	}

public:

	/**
	 * Returns the vector of observers currently subscribed.
	 * @return the observers
	 */
	std::vector<std::reference_wrapper<Observer>> &observers() {
		return _observers;
	}

	/**
	 * Adds the specified observer to the list of observers.
	 * @param observer the subscribing observer
	 */
	const void subscribe(Observer &observer) {
		// catch re-adding same observer
		for (Observer &o : _observers) {
			if (&o == &observer) return;
		}

		_observers.emplace_back(observer);
	}

	/**
	 * Unsubscribes the specified observer.
	 * @param observer the unsubscribing observer
	 */
	const void unsubscribe(Observer &observer) {
		auto comparator = [&observer](Observer &element) -> bool {
			return &element == &observer;
		};
		auto iterator = std::find_if(std::begin(_observers), std::end(_observers), comparator);
		_observers.erase(iterator);
	}
};

#endif //PSE_BEE_GAME_OBSERVABLE_H
