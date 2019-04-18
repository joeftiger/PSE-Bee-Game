//
// Created by brian on 25/03/2019.
//

#ifndef _OPTIONSSCENE_H
#define _OPTIONSSCENE_H

#include "MainMenu/MainMenuScene.h"
#include "Game/TileMapLayer.h"
#include "SaveLoad/SaveLoad.h"
#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class OptionsScene : public cocos2d::Scene {
private:

	float onePofScreenH;
	float onePofScreenW;

public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	void onDeleteSaveClick(cocos2d::Ref *sender);

	// implement the "static create()" method manually
	CREATE_FUNC(OptionsScene);
};


#endif //_OPTIONSSCENE_H
