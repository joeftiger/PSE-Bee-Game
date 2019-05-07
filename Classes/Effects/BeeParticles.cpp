//
// Created by uro on 5/5/19.
//

#include <Resources/SpriteContainer.h>
#include "BeeParticles.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

Node *BeeParticles::createNode() {return BeeParticles::create();}

bool BeeParticles::init() {
    if (!Node::init()) {
        return false;
    }

    this->schedule(schedule_selector(BeeParticles::nextParticlesPos), 0.033f);
    this->setQuantity(30000);

    return true;
}

void BeeParticles::nextParticlesPos(float dt) {
    for(auto particle : _particles) {
        if(particle->getPosition().length() >= 70) {
            particle->setPosition(0,0);
        } else {
            particle->setPosition(Vec2(particle->getPosition().x + random(-2.0, 2.0), particle->getPosition().y + random(-2.0, 2.0)));
        }
    }
}

void BeeParticles::setQuantity(int bees) {
    bees /= 500;

    updateList(_quantity - bees);

    _quantity = bees;
}

void BeeParticles::updateList(int delta) {
    if(delta > 0) {
        for(int i = 0; i < delta; i++) {
            this->removeChild(_particles.back());
            _particles.pop_back();
        }
    } else if(delta < 0) {
        for(int i = 0; i < abs(delta); i++) {
            auto temp = SpriteContainer::getInstance()->getSpriteOf(Sprites::honey_glass_2d);
            temp->setScale(0.03);
            _particles.push_back(temp);
            this->addChild(temp);
        }
    }
}