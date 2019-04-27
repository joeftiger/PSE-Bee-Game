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


double GameAlgorithm::honeyProduction(int bees) {
    double honey;
    if(Time::getInstance()->getMonth() <= 9 && Time::getInstance()->getMonth() > 3) {
        honey = bees * HONEY_PER_BEE;
    }


    //TODO add other variables like flowers and seasons.

    return honey;
}

int GameAlgorithm::nextBees(int bees, int varroa) {
    int newBees;
    if(Time::getInstance()->getMonth() <= 7 && Time::getInstance()->getMonth() > 4) {
        newBees += BEES_PER_UPDATE;
    }
    newBees -= varroa * VARROA_KILL_RATE;

    newBees -= BEES_DEAD_PER_UPDATE;
    return newBees;
}

int GameAlgorithm::nextVarroa(int varroa) {
    _varroaCounter++;
    if(_varroaCounter >= 59) {
        _varroaCounter = 0;
        return varroa;
    } else {return 0;}
}

void GameAlgorithm::setBeeHives() {
    BeeHiveAtlas::getInstance()->getBeeHives(_beeHives);
}