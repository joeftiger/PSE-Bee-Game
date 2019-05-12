

#ifndef _ABOUTSCENE_H
#define _ABOUTSCENE_H

#include "MainMenu/MainMenuScene.h"
#include "cocos2d.h"
#include "ui/UIRichText.h"

/**
 * About Scene with a short description of the app, contributers, etc.
 */
using namespace cocos2d;

class AboutScene : public cocos2d::Scene {
private:

	float onePofScreenH;
	float onePofScreenW;

public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(AboutScene);
};

#endif //_ABOUTSCENE_H