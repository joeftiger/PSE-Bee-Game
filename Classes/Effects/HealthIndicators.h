
#ifndef HEALTHINDICATORS_H
#define HEALTHINDICATORS_H

#include "cocos2d.h"

using namespace cocos2d;

/**
 * Health Indicators that are used on each beeHive to display their approximate health
 */
class HealthIndicators : public Node {
private:

public:
	static Node *createNode();
	virtual bool init();


    CREATE_FUNC(HealthIndicators);
};

#endif //HEALTHINDICATORS_H
