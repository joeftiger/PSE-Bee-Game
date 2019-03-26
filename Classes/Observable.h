//
// Created by julius on 24.03.19.
//

#ifndef PSE_BEE_GAME_OBSERVABLE_H
#define PSE_BEE_GAME_OBSERVABLE_H

#include "Observer.h"

class Observable {
private:

	/** observers having subscribed to this observable */
	std::vector<Observer *> _observers;

	/**
	 * Should notify all observers of a change in this observable.
	 */
	const virtual void notifyObservers() {
		for (auto o : _observers) {
			o->notify(this);
		}
	}

public:

	/**
	 * Returns the vector of observers currently subscribed.
	 * @return the observers
	 */
	std::vector<Observer *> *observers() {
		return &_observers;
	}
	/**
	 * Adds the specified observer to the list of observers.
	 * @param observer the subscribing observer
	 */
	const void subscribe(Observer *observer) {
		// catch re-adding same observer
		for (auto o : _observers) {
			if (o == observer) return;
		}

		_observers.push_back(observer);
	}

	/**
	 * Unsubscribes the specified observer.
	 * @param observer the unsubscribing observer
	 */
	const void unsubscribe(Observer *observer) {
		// TODO: Make this more efficient. I noticed std::vector is somewhat limited.
		long pos = -1;
		for (int i = 0; i < _observers.size(); i++) {
			if (_observers.at(i) == observer) {
				pos = i;
				break;
			}
		}

		if (pos != -1) {
			_observers.erase(_observers.begin() + pos);
		}
	}
};

#endif //PSE_BEE_GAME_OBSERVABLE_H
