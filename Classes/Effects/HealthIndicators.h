
#ifndef HEALTHINDICATORS_H
#define HEALTHINDICATORS_H

#include "cocos2d.h"

using namespace cocos2d;

/**
 * Health Indicators that are used on each beeHive to display their approximate health
 */
class HealthIndicators : public Node {
private:
	std::vector<Sprite*> _indicators;

public:
	static Node *createNode();
	virtual bool init();


	/**
     * Updates particle positions scheduled for every frame.
     * TODO Replace or adjust this method
     * @param dt
     */
    void nextParticlesPos(float dt);

	/**
     * updates particles.
     * TODO this whole method
     * @param delta. Difference of current bees and previous bees.
     */
	void update(int delta);

    CREATE_FUNC(HealthIndicators);
};

#endif //HEALTHINDICATORS_H
