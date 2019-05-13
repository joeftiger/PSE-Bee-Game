
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
    //bool state;
    bool firstTime0 = true;
    bool firstTime1 = true;
    bool firstTime2 = true;
    bool firstTime3 = true;
    bool firstTime4 = true;

public:
    static StoryScene *getInstance() {
        static auto instance = new StoryScene();
        return instance;
    }
	virtual bool init();
	//void introPopup();
	//void update(float dt) override;
	UICustom::Popup* createPopup(int);

	CREATE_FUNC(StoryScene);

    /**
     * Saving and loading states in "story.json" if the popup has shown already
     * @param doc
     */
    void toJSON(rapidjson::Document &doc) ;
    void fromJSON(rapidjson::Document &doc) ;

    /**
     *  Call this to disable Story Popups
     */
     void skipTutorial();
};


#endif //__STORY_SCENE_H
