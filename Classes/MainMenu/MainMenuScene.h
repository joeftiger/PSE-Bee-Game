
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "Game/GameScene.h"
#include "About/AboutScene.h"
#include "Options/OptionsScene.h"
#include "cocos2d.h"
#include "ui/UIWidget.h"

class MainMenu : public cocos2d::Scene {
private:
	float onePofScreenH;
	float onePofScreenW;
public:
	static cocos2d::Scene *scene();

	virtual bool init();

	// Play Click Handler
	void onPlayClick(cocos2d::Ref *sender);

	// Options Click Handler
	void onOptionsClick(cocos2d::Ref *sender);

	// About Click Handler
	void onAboutClick(cocos2d::Ref *sender);

	// Exit Click Handler
	void onExitClick(cocos2d::Ref *sender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__