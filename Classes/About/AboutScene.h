//
// Created by brian on 25/03/2019.
//

#ifndef _ABOUTSCENE_H
#define _ABOUTSCENE_H

#include "MainMenu/MainMenuScene.h"
#include "cocos2d.h"
#include "ui/UIRichText.h"


using namespace cocos2d;

class AboutScene : public cocos2d::Scene
{
private:

	float onePofScreenH;
    float onePofScreenW;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(AboutScene);
};


#endif //_ABOUTSCENE_H
