
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "HeaderFiles/TileGID.h"
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

	//camera
	camera = this->getDefaultCamera();
	this->removeChild(camera);

	// Background TileMap
	_tileMapLayer = TileMapLayer::create();
	this->addChild(_tileMapLayer, -1);

	// TileMapAtlas and observe TileMap
	auto tileMapAtlas = BeeHiveAtlas::getInstance();
	_tileMapLayer->subscribe(*tileMapAtlas);
	this->getScheduler()->schedule(schedule_selector(BeeHiveAtlas::update), tileMapAtlas,1.0f, false);

	// getInstance() subscribes to TileMapAtlas, if not called already
	Player::getInstance();
	tileMapAtlas->notify(_tileMapLayer);

	//HUD Layer
	_HUDLayer = HUDLayer::create();

	//Item Panel
	_itemPanel = ItemPanelLayer::create();

	//camera and huds container
	container = Node::create();
	container->addChild(camera);
	this->addChild(container);
	container->addChild(_itemPanel);
	container->addChild(_HUDLayer);
	container->setPosition(Vec2(_tileMapLayer->getMap()->getBoundingBox().size.width/2 - visibleSize.width/2, _tileMapLayer->getMap()->getBoundingBox().size.height/2 - visibleSize.height/2));
	cameraTravel -= container->getPosition();

	this->schedule(schedule_selector(GameScene::saveGameState), 60);
	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	_isTouched = true;
	_touchPosition = touch->getLocation();
	_itemPanel->showHideItemPanel(_touchPosition);
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
	auto touchPos = touch->getLocation();
	auto movement = touchPos - _touchPosition;
	_touchPosition = touchPos;


	if (_itemPanel->isDrag()) {
		_itemPanel->getDrag()->setPosition(touchPos - _itemPanel->getPosition());
	} else {
		cameraTravel += movement;
		container->setPosition(container->getPosition() - movement);
	}
}

void GameScene::onTouchEnded(void *, void *) {
	if (_itemPanel->isDrag()) {
		auto pos = _touchPosition - cameraTravel;
		auto gid = _itemPanel->getDrag()->getTag();

		if (_tileMapLayer->canSetTile(pos, gid)) {
			_tileMapLayer->setTile(pos, gid);
		}

		_itemPanel->removeChild(_itemPanel->getDrag());
		_itemPanel->setIsDrag(false);
	}
	_isTouched = false;
}

void GameScene::saveGameState(float dt) {
	SaveLoad::saveMap();
	//TODO: Add beehives here or create general method in saveload
}

