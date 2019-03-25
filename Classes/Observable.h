//
// Created by julius on 24.03.19.
//

#ifndef PSE_BEE_GAME_OBSERVABLE_H
#define PSE_BEE_GAME_OBSERVABLE_H

#include "Observer.h"

class Observable {
private:
	virtual void notifyObservers() = 0;
public:
	virtual void subscribe(Observer *observer) = 0;
};

#endif //PSE_BEE_GAME_OBSERVABLE_H
