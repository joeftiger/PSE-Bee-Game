
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__


#include "cocos2d.h"
#include "ui/UIWidget.h"

/**
 * a main menu scene with interactable buttons that lead to the game, options & about scene
 * as well as a button to exit the game
 */
class MainMenu : public cocos2d::Scene {
private:
	float onePofScreenH;
	float onePofScreenW;
public:
	static cocos2d::Scene *scene();

	virtual bool init();

	// Play Click Handler
	void onPlayClick();

	// Options Click Handler
	void onOptionsClick();

	// About Click Handler
	void onAboutClick();

	// Exit Click Handler
	void onExitClick();

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__