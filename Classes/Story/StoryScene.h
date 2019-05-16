
#ifndef __STORY_SCENE_H
#define __STORY_SCENE_H

#include "cocos2d.h"
#include "Game/Time.h"
#include "Popup.h"

using namespace cocos2d;

/**
 * Story dialogue via pop-ups that display text with the "granddaddy" sprite
 */
class StoryScene {
private:
    Time* time;
    std::vector<bool> popups;

    StoryScene();

public:
    static StoryScene *getInstance() {
        static auto instance = new StoryScene();
        return instance;
    }

	void init();

    /**
     * creates a popup with a given ID:
     * 0 = Intro
     * 1 = Beehive
     * 2 = Varroa
     * 3 = Shop
     * 4 = First Winter Info
     * 5 = First beehive dead
     * @return the popup
     */
	UICustom::Popup* createPopup(int);


    /**
     * Saving and loading states in "story.json" if the popup has shown already
     * @param doc
     */
    void toJSON(rapidjson::Document &doc) ;
    void fromJSON(rapidjson::Document &doc) ;

    /**
     *  pass boolean value to set tutorial visibility
     */
     void setTutorial(bool value);
};


#endif //__STORY_SCENE_H
