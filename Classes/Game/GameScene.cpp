
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "HeaderFiles/TileGID.h"
#include "SaveLoad/SaveLoad.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "AppDelegate.h"


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

	container->setPosition(Vec2(2000, 2000));
	cameraTravel -= container->getPosition();
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
		_tileMapLayer->setTile(_touchPosition - cameraTravel, _itemPanel->getDrag()->getTag());
		_itemPanel->removeChild(_itemPanel->getDrag());
		_itemPanel->setIsDrag(false);
	}
	_isTouched = false;
}


