
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "GameScene.h"
#include "cocos2d.h"
#include "ui/UIWidget.h"

class MainMenu : public cocos2d::Scene
{
private:
public:
    static cocos2d::Scene* scene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	//New Game Click Handler
	void onNewGameClick(cocos2d::Ref * sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__