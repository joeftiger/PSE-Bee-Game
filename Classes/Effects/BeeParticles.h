
#ifndef PSE_BEE_GAME_BEEPARTICLES_H
#define PSE_BEE_GAME_BEEPARTICLES_H

#include "cocos2d.h"

using namespace cocos2d;

/**
 * Creating a certain amount of "bee" particles for a BeeHive, with a slightly randomized path. Amount of particles is dependend on amount of bees in the BeeHive
 */
class BeeParticles : public Node {
private:
    std::vector<Sprite*> _particles;
    int _quantity;
public:

    static Node *createNode();
    virtual bool init();

    void nextParticlesPos(float dt);
    void setQuantity(int bees);
    void updateList(int delta);

    CREATE_FUNC(BeeParticles);
};


#endif //PSE_BEE_GAME_BEEPARTICLES_H
