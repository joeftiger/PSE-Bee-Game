
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "HeaderFiles/DEFINITIONS.h"
#include "HUDLayer.h"
#include "TileMapLayer.h"
#include "cocos2d.h"
#include "ItemPanel/TouchUtil.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "Time.h"


using namespace cocos2d;

class GameScene : public cocos2d::Scene {
private:
	Camera *_camera;
	TileMapLayer *_tileMapLayer;
	HUDLayer *_HUDLayer;

	bool _isTouched;

	ItemPanelLayer *_itemPanel;

	Time *time;

public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	void beeHiveAtlasUpdate(float dt);

	bool onTouchBegan(Touch *touch, Event *event);

	void onTouchMoved(Touch *touch, Event *event);

	void onTouchEnded(Touch *touch, Event *event);

	void saveGameState(float dt);

	void touchOnItemPanel();

	void ShowHideItemPanel();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
