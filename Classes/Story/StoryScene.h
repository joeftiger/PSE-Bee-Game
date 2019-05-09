
#ifndef __STORY_SCENE_H
#define __STORY_SCENE_H

#include "cocos2d.h"
#include "Game/Time.h"
#include "Popup.h"

using namespace cocos2d;

/**
 * Story dialogue via pop-ups that display text with the "granddaddy" sprite
 */
class StoryScene : public cocos2d::Node {
private:
    Time* time;
    bool state;
public:

	virtual bool init();
	//void introPopup();
	//void update(float dt) override;
	UICustom::Popup* createPopup(int);

	CREATE_FUNC(StoryScene);

};


#endif //__STORY_SCENE_H
