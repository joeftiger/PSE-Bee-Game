

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "MainMenuScene.h"
#include "TileMapLayer.h"
#include "cocos2d.h"


using namespace cocos2d;

class GameScene: public cocos2d::Scene
{
private:
    cocos2d::Layer *_tileMapLayer;

    bool _isTouched;
    Point _touchPosition;

	unsigned int honey;
	Label *honeyLabel;

	float timePassed;
	Label *timeLabel;

public:
    static cocos2d::Scene* createScene();
	virtual bool init();

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(void *, void *);

	Vec2 getclosestTile(Vec2 t);

	void timer(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
