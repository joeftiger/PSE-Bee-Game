
#include <Game/Time.h>
#include "GameAlgorithm.h"
#include "Game/BeeHive.h"
GameAlgorithm *GameAlgorithm::_instance = nullptr;

GameAlgorithm *GameAlgorithm::getInstance() {
    if (!_instance) {
        cocos2d::log("GameAlgorithm:\tCreating instance");
        _instance = new GameAlgorithm;
    }

    return _instance;
}


float GameAlgorithm::honeyProduction(int bees, int food) {
    float honey;
    if(Time::getInstance()->getMonth() <= 8 && Time::getInstance()->getMonth() > 2) {
        honey = bees * HONEY_PER_BEE;
    }

    if(food <= 0) {
        honey -= bees * FOOD_EATEN_PER_BEE;
    }


    //TODO add other variables like flowers.

    return honey;
}

int GameAlgorithm::nextBees(float bees, float varroa, float food, float honey) {
    int newBees;

    if(Time::getInstance()->getSeason() == Season::Spring) {
        newBees += BEES_PER_UPDATE;
    } else if(Time::getInstance()->getSeason() == Season::Fall) {
        newBees -= 130;
    }

    newBees = newBees - BEES_DEAD_PER_UPDATE;

    newBees -= varroa * VARROA_KILL_RATE;

    if(food <= 0 && honey <= 0) {
        newBees -= 200;
    }

    return newBees;
}

int GameAlgorithm::nextVarroa(float bees, int varroa) {
    _varroaCounter++;
    if(_varroaCounter >= 19) {
        _varroaCounter = 0;
        float ratio = bees/MAX_BEES;

        return varroa * ratio + 1;
    } else {return 0;}
}

void GameAlgorithm::setBeeHives() {
    BeeHiveAtlas::getInstance()->getBeeHives(_beeHives);
}

int GameAlgorithm::foodConsumption(int bees) {
    return bees * FOOD_EATEN_PER_BEE;
}