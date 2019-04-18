
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "SaveLoad/SaveLoad.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "AppDelegate.h"
#include "Player.h"


using namespace cocos2d;

Scene *GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init()) return false;

	Size visibleSize = Director::getInstance()->getWinSize();
	//Director::getInstance()->setClearColor(Color4F(0.5,0.73,0.14,1));

	// Touch Event Listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Background TileMap
	_tileMapLayer = TileMapLayer::create();
	this->addChild(_tileMapLayer, -1);

	// TileMapAtlas and observe TileMap
	auto tileMapAtlas = BeeHiveAtlas::getInstance();
	_tileMapLayer->subscribe(*tileMapAtlas);
	//this->scheduleUpdate();
	//this->getScheduler()->schedule(schedule_selector(BeeHiveAtlas::updateBeeHives), tileMapAtlas,1.0f, false, s);

	// getInstance() subscribes to TileMapAtlas, if not called already
	Player::getInstance();
	tileMapAtlas->notify(_tileMapLayer);

	time = Time::createInstance();
	this->addChild(time);
	if (SaveLoad::timesSaveExists()) {
		SaveLoad::loadTime();
	}

	//HUD + ItemPanel Layer
	_HUDLayer = HUDLayer::create();
	this->addChild(_HUDLayer, HUD_PRIORITY);
	_itemPanel = ItemPanelLayer::create();
	_HUDLayer->addChild(_itemPanel);

	// camera
	_camera = this->getDefaultCamera();

	this->schedule(schedule_selector(GameScene::saveGameState), 60.0f);
	this->schedule(schedule_selector(GameScene::beeHiveAtlasUpdate), 1.0f);
	return true;
}

/**
	Calls BeeHiveUpdate every dt seconds
*/
void GameScene::beeHiveAtlasUpdate(float dt) {
	BeeHiveAtlas::getInstance()->updateBeeHives(dt);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	_isTouched = true;
	_itemPanel->showHideItemPanel(touch->getLocation());
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
	auto movement = touch->getPreviousLocation() - touch->getLocation();

	if (_itemPanel->isDrag()) {
		_itemPanel->getDrag()->setPosition(_itemPanel->getPosition() + movement);
	} else {
		auto cameraPos = _camera->getPosition();
		_camera->setPosition(cameraPos + movement);

		auto hudPos = _HUDLayer->getPosition();
		_HUDLayer->setPosition(hudPos + movement);
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *event) {
	if (_itemPanel->isDrag()) {
		auto pos = touch->getLocation();
		auto gid = _itemPanel->getDrag()->getTag();

		if (_tileMapLayer->canPlaceTile(pos, gid)) {
			_tileMapLayer->placeTile(pos, gid);
		}

		_itemPanel->removeChild(_itemPanel->getDrag());
		_itemPanel->setIsDrag(false);
	}
	_isTouched = false;
}

void GameScene::saveGameState(float dt) {
	SaveLoad::saveMap();
	SaveLoad::saveBeehives();
	//TODO: Add beehives here or create general method in saveload
}

