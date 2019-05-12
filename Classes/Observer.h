
#ifndef PSE_BEE_GAME_OBSERVER_H
#define PSE_BEE_GAME_OBSERVER_H

/**
 * Observer that can be notified of changes and then respond or react accordingly
 */
class Observer {
public:
	/**
	 * Notifies this observer of a change in the observable.
	 */
	virtual void notify(void *) = 0;
};

#endif //PSE_BEE_GAME_OBSERVER_H
