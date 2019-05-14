
#ifndef OBSERVER_H
#define OBSERVER_H

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

#endif //OBSERVER_H
