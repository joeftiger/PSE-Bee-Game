
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "DEFINITIONS.h"
#include "HUDLayer.h"
#include "TileMapLayer.h"
#include "cocos2d.h"


using namespace cocos2d;

class GameScene: public cocos2d::Scene
{
private:
    TileMapLayer *_tileMapLayer;
	HUDLayer *_HUDLayer;

    bool _isTouched;
    Point _touchPosition;

	Sprite *flower1;
	Sprite *drag;
	bool _isDrag;

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
