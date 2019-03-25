//
// Created by julius on 24.03.19.
//

#ifndef PSE_BEE_GAME_OBSERVABLE_H
#define PSE_BEE_GAME_OBSERVABLE_H

#include "Observer.h"

class Observable {
private:
	/**
	 * Should notify all observers of a change in this observable.
	 */
	virtual void notifyObservers() = 0;
public:
	/**
	 * Adds the specified observer to the list of observers.
	 * @param observer the subscribing observer
	 */
	virtual void subscribe(Observer *observer) = 0;
};

#endif //PSE_BEE_GAME_OBSERVABLE_H
