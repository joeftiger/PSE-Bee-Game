
#include "../Resources/SpriteContainer.h"
#include "../HeaderFiles/HealthStates.h"
#include "HealthIndicators.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

Node *HealthIndicators::createNode() {return HealthIndicators::create();}

bool HealthIndicators::init() {
    if (!Node::init()) {
        return false;
    }
    this->schedule(schedule_selector(HealthIndicators::nextParticlesPos), 0.033f);
    this->update(123);

    return true;
}

void HealthIndicators::setHealth(HealthState _currentHealth) {

	// initialize with "healthy" image
	auto stateImage = Sprite::create("indicators/greenSquare.png");

	if (_currentHealth == Healthy) {
		stateImage = Sprite::create("indicators/greenSquare.png");
    } else if (_currentHealth == Average) {
		stateImage = Sprite::create("indicators/yellowSquare.png");
	} else if (_currentHealth == Unhealthy) {
		stateImage = Sprite::create("indicators/redSquare.png");
    } else { //dead
        stateImage = Sprite::create("indicators/blackSquare.png");
    }

    stateImage->setScale(0.4f); //TODO Mess around with this when played
    _indicators.push_back(stateImage);
    this->addChild(stateImage);

}

void HealthIndicators::update(int delta) {
    if(delta > 0) {
        for(int i = 0; i < delta; i++) {
            this->removeChild(_indicators.back());
            _indicators.pop_back();
        }
    } else if(delta < 0) {
        for(int i = 0; i < abs(delta); i++) {
            auto temp = SpriteContainer::getInstance()->getSpriteOf(Sprites::honey_glass_2d);
            temp->setScale(0.03);
            _indicators.push_back(temp);
            this->addChild(temp);
        }
    }
}