
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "HeaderFiles/DEFINITIONS.h"
#include "HUDLayer.h"
#include "TileMapLayer.h"
#include "cocos2d.h"
#include "ItemPanel/TouchUtil.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "Time.h"
#include "HoneyExtractor.h"

using namespace cocos2d;

/**
 * The GameScene that has a HUDLayer and deals with collecting and connecting the game's logic
 */
class GameScene : public cocos2d::Scene {
private:
	Camera *camera;
	TileMapLayer *_tileMapLayer;
	HUDLayer *_HUDLayer;

	Node *container;
	HoneyExtractor * extractor;

	ItemPanelLayer *_itemPanel;

	Time *time;

public:

	virtual bool init() override;

	/**
     *	Calls BeeHiveUpdate every dt seconds
     */
	void beeHiveAtlasUpdate(float dt);

	/**
     *	Calls HoneyExtractorUpdate every dt seconds
     */
	void honeyExtractorAtlasUpdate(float dt);

	bool onTouchBegan(Touch *touch, Event *event);

	void onTouchMoved(Touch *touch, Event *event);

	void onTouchEnded(Touch *touch, Event *event);

	void saveGameState(float dt);

	Node* getCameraContainer();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
