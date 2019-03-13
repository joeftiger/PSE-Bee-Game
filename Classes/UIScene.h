//
// Created by tb18a517 on 13.03.2019.
//

#ifndef __UI_SCENE_H
#define __UI_SCENE_H

#include "cocos2d.h"

using namespace cocos2d;

class UIScene: public cocos2d::Scene {


public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(UIScene);
};


#endif //__UI_SCENE_H
