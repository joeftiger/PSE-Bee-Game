
#include "GameScene.h"
#include "Atlas/BeeHiveAtlas.h"
#include "Atlas/HoneyExtractorAtlas.h"
#include "SaveLoad/SaveLoad.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "AppDelegate.h"
#include "Player.h"


using namespace cocos2d;

Scene *GameScene::createScene() {	return GameScene::create(); }

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

	auto honeyExtractorAtlas = HoneyExtractorAtlas::getInstance();
    _tileMapLayer->subscribe(*honeyExtractorAtlas);

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
	else {
		time->setStartingMonth();
	}

	//HUD Layer
	_HUDLayer = HUDLayer::create();

	//Item Panel
	_itemPanel = ItemPanelLayer::create();
	_itemPanel->setTileMap(_tileMapLayer);

	//camera and huds container
	container = Node::create();
	container->addChild(camera);
	this->addChild(container);
	container->addChild(_itemPanel);
	container->addChild(_HUDLayer);
	container->setPosition(Vec2(_tileMapLayer->getMap()->getBoundingBox().size.width / 2 - visibleSize.width / 2,
	                            _tileMapLayer->getMap()->getBoundingBox().size.height / 2 - visibleSize.height / 2));

	this->schedule(schedule_selector(GameScene::saveGameState), 60.0f);
	this->schedule(schedule_selector(GameScene::beeHiveAtlasUpdate), 1.0f);
	this->schedule(schedule_selector(GameScene::honeyExtractorAtlasUpdate), 1.0f);
	return true;
}

/**
 *	Calls BeeHiveUpdate every dt seconds
 */
void GameScene::beeHiveAtlasUpdate(float dt) {
	BeeHiveAtlas::getInstance()->updateBeeHives(dt);
}

/**
 *	Calls HoneyExtractorUpdate every dt seconds
 */
void GameScene::honeyExtractorAtlasUpdate(float dt) {
	HoneyExtractorAtlas::getInstance()->updateHoneyExtractors(dt);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	_itemPanel->showHideItemPanel(touch->getLocation() - container->getPosition());
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
	auto movement = touch->getLocation() - touch->getPreviousLocation();

	if (!_itemPanel->isDrag()) {
		container->setPosition(container->getPosition() - movement);
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *event) {
    auto pos = touch->getLocation() + container->getPosition();	// note it's (+) now
	//if(!_isMoved) {
        interactAt(pos);
	//}
}

void GameScene::interactAt(const Vec2& pos) {
    auto selectTilePos = _tileMapLayer->getTilePosition(pos);

    if(BeeHiveAtlas::getInstance()->hasBeeHiveAt(selectTilePos)) {
        auto beeHive = BeeHiveAtlas::getInstance()->getBeeHiveAt(selectTilePos);
        Interacter *i = Interacter::create();
        this->addChild(i, 100);
        i->runWith(beeHive);
        i->interact();

    } else if(HoneyExtractorAtlas::getInstance()->hasHoneyExtractorAt(selectTilePos)) {
		auto honeyExtractor = HoneyExtractorAtlas::getInstance()->getHoneyExtractorAt(selectTilePos);
		Interacter *i = Interacter::create();
		this->addChild(i, 100);
		i->runWith(honeyExtractor);
		i->interact();
    }
}

void GameScene::saveGameState(float dt) {
	SaveLoad::saveEverything();
}

Node* GameScene::getCameraContainer() {
    return container;
}

