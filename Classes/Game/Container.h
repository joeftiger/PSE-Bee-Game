//
// Created by Uro on 4/1/2019.
//

#ifndef PSE_BEE_GAME_CONTAINER_H
#define PSE_BEE_GAME_CONTAINER_H


#include <cocos/2d/CCScene.h>

class Container: public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Container);
};


#endif //PSE_BEE_GAME_CONTAINER_H
