//
// Created by brian on 24/04/2019.
//

#ifndef PROJ_ANDROID_SAVEDELETECONFIRMATION_H
#define PROJ_ANDROID_SAVEDELETECONFIRMATION_H

#include "MainMenu/MainMenuScene.h"
#include "OptionsScene.h"
#include "SaveLoad/SaveLoad.h"
#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;

class SaveDeleteConfirmation : public cocos2d::Scene {
private:

	float onePofScreenH;
	float onePofScreenW;

public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	// Yes Click Handler
    void onYesClick(cocos2d::Ref *sender);

    // No Click Handler
    void onNoClick(cocos2d::Ref *sender);

	// implement the "static create()" method manually
	CREATE_FUNC(SaveDeleteConfirmation);
};

#endif //PROJ_ANDROID_SAVEDELETECONFIRMATION_H
