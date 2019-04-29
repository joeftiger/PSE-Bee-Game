
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "HeaderFiles/DEFINITIONS.h"
#include "HUDLayer.h"
#include "TileMapLayer.h"
#include "cocos2d.h"
#include "ItemPanel/TouchUtil.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "Time.h"
#include "Interacter.h"


using namespace cocos2d;

class GameScene : public cocos2d::Scene {
private:
	Camera *camera;
	TileMapLayer *_tileMapLayer;
	HUDLayer *_HUDLayer;

	Node *container;

	ItemPanelLayer *_itemPanel;

	Time *time;

public:
	static cocos2d::Scene *createScene();

	virtual bool init() override;

	void beeHiveAtlasUpdate(float dt);

	void honeyExtractorAtlasUpdate(float dt);

	bool onTouchBegan(Touch *touch, Event *event);

	void onTouchMoved(Touch *touch, Event *event);

	void onTouchEnded(Touch *touch, Event *event);

	void saveGameState(float dt);

	void interactAt(Vec2 pos);

	Node* getCameraContainer();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
