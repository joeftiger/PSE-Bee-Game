//
// Created by uro on 4/25/19.
//

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


float GameAlgorithm::honeyProduction(int bees) {
    float honey;
    if(Time::getInstance()->getMonth() <= 8 && Time::getInstance()->getMonth() > 2) {
        honey = bees * HONEY_PER_BEE;
    }


    //TODO add other variables like flowers.

    return honey;
}

int GameAlgorithm::nextBees(int bees, int varroa, int full) {
    int newBees;

    if(Time::getInstance()->getMonth() <= 7 && Time::getInstance()->getMonth() > 4 && !full) {
        newBees += BEES_PER_UPDATE;
    }

    newBees -= BEES_DEAD_PER_UPDATE;

    newBees -= varroa * VARROA_KILL_RATE;

    return newBees;
}

int GameAlgorithm::nextVarroa(int varroa) {
    _varroaCounter++;
    if(_varroaCounter >= 19) {
        _varroaCounter = 0;
        return varroa;
    } else {return 0;}
}

void GameAlgorithm::setBeeHives() {
    BeeHiveAtlas::getInstance()->getBeeHives(_beeHives);
}