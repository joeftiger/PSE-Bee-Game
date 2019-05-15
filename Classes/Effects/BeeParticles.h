
#ifndef BEEPARTICLES_H
#define BEEPARTICLES_H

#include "cocos2d.h"

using namespace cocos2d;

/**
 * Creating a certain amount of "bee" particles for a BeeHive, with a slightly randomized path.
 * Amount of particles is dependend on amount of bees in the BeeHive
 */
class BeeParticles : public Node {
private:
    std::vector<Sprite*> _particles;
    int _quantity;
public:

    static Node *createNode();
    virtual bool init();

    /**
     * Updates particle positions scheduled for every frame.
     *
     * @param dt
     */
    void nextParticlesPos(float dt);

    /**
     * Particles are the amount of bees divided by 500.
     * @param bees
     */
    void setQuantity(int bees);

    /**
     * Removes or adds particles to the list of particles.
     *
     * @param delta. Difference of current bees and previous bees.
     */
    void updateList(int delta);

    CREATE_FUNC(BeeParticles);
};


#endif //BEEPARTICLES_H
