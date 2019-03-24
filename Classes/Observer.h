//
// Created by julius on 24.03.19.
//

#ifndef PSE_BEE_GAME_OBSERVER_H
#define PSE_BEE_GAME_OBSERVER_H

class Observer {
public:
	/**
	 * Notifies this observer of a change in the observable.
	 */
	virtual void notify(void *) = 0;
};

#endif //PSE_BEE_GAME_OBSERVER_H
