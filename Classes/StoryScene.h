

#ifndef __STORY_SCENE_H
#define __STORY_SCENE_H

#include "cocos2d.h"

using namespace cocos2d;

class StoryScene: public cocos2d::Scene {

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(StoryScene);

};


#endif //__STORY_SCENE_H
