
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "HeaderFiles/DEFINITIONS.h"
#include "HUDLayer.h"
#include "TileMapLayer.h"
#include "cocos2d.h"
#include "TouchUtil.h"
#include "ItemPanelLayer.h"


using namespace cocos2d;

class GameScene: public cocos2d::Scene, public TouchUtil
{
private:
    Size visibleSize;
    TileMapLayer *_tileMapLayer;
	HUDLayer *_HUDLayer;

    bool _isTouched;
    bool _isItemShow = false;
    Point _touchPosition;

    ItemPanelLayer *_itemPanel;

public:
    static cocos2d::Scene* createScene();
	virtual bool init();

	void placeFlower(Sprite *flower);

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(void *, void *);

    void touchOnItemPanel();
    void ShowHideItemPanel();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
