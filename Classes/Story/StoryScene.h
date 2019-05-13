
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

    /**
     * creates a popup with a gived ID:
     * 0 = Intro
     * 1 = Beehive
     * 2 = Varroa
     * 3 = Shop
     * 4 = First Winter Info
     * @return the popup
     */
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
