//
// Created by Tobias on 27.04.2019.
//

#ifndef PROJ_ANDROID_INTERACTER_H
#define PROJ_ANDROID_INTERACTER_H

#include "cocos2d.h"
#include "../HeaderFiles/Interactable.h"
#include "Interaction/InteractionNode.h"
#include "GameScene.h"

using namespace cocos2d;

class Interacter : public cocos2d::Node {

private:

    Interactable *interactingObj;

public:

    virtual bool init() override;

    void runWith(Interactable *interactingObj);

    void interact();

    CREATE_FUNC(Interacter);
};


#endif //PROJ_ANDROID_INTERACTER_H
