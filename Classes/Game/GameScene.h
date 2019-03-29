
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "HeaderFiles/DEFINITIONS.h"
#include "HUDLayer.h"
#include "TileMapLayer.h"
#include "cocos2d.h"
#include "TouchUtil.h"


using namespace cocos2d;

class GameScene: public cocos2d::Scene, private TouchUtil
{
private:
    TileMapLayer *_tileMapLayer;
	HUDLayer *_HUDLayer;

    bool _isTouched;
    Point _touchPosition;

public:
    static cocos2d::Scene* createScene();
	virtual bool init();

	void placeFlower(Sprite *flower);

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(void *, void *);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
