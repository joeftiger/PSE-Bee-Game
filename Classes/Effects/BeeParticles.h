//
// Created by uro on 5/5/19.
//

#ifndef PSE_BEE_GAME_BEEPARTICLES_H
#define PSE_BEE_GAME_BEEPARTICLES_H

#include "cocos2d.h"

using namespace cocos2d;

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
