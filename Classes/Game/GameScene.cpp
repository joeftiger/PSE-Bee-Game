
#include <Interaction/BeeHivePopup.h>
#include <Resources/SpriteContainer.h>
#include <Effects/BeeParticles.h>
#include "GameScene.h"
#include "Atlas/BeeHiveAtlas.h"
#include "Atlas/HoneyExtractorAtlas.h"
#include "SaveLoad/SaveLoad.h"
#include "ItemPanel/ItemPanelLayer.h"
#include "AppDelegate.h"
#include "Player.h"
#include "Interaction/HoneyExtractorPopup.h"
#include "Interaction/HoneyMover.h"
#include "Story/StoryScene.h"


using namespace cocos2d;

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

	//Time
	
	auto time = Time::getInstance();
	time->setTileMapLayer(_tileMapLayer);

	if (SaveLoad::timesSaveExists()) {
		SaveLoad::loadTime();
	}

	// TileMapAtlas and observe TileMap
	auto tileMapAtlas = BeeHiveAtlas::getInstance();
	_tileMapLayer->subscribe(*tileMapAtlas);

	auto honeyExtractorAtlas = HoneyExtractorAtlas::getInstance();
    _tileMapLayer->subscribe(*honeyExtractorAtlas);

	// getInstance() subscribes to TileMapAtlas, if not called already
	Player::getInstance();
	tileMapAtlas->notify(_tileMapLayer);
	honeyExtractorAtlas->notify(_tileMapLayer);

	if (SaveLoad::moneySaveExists()) {
		SaveLoad::loadMoney();
	}

	StoryScene::getInstance()->init();

	//HUD Layer
	_HUDLayer = HUDLayer::create();

	//Item Panel
	_itemPanel = ItemPanelLayer::create();
	_itemPanel->setTileMap(_tileMapLayer);

	// camera and HUD container
	container = Node::create();
	container->addChild(camera);
	this->addChild(container,HUD_PRIORITY, "container");
	container->addChild(_itemPanel);
	container->addChild(_HUDLayer);
	container->setPosition(Vec2(_tileMapLayer->getMap()->getBoundingBox().size.width / 2 - visibleSize.width / 2,
	                            _tileMapLayer->getMap()->getBoundingBox().size.height / 2 - visibleSize.height / 2));

    //provisory extractor
    HoneyMover* honeyMover = HoneyMover::create();
    honeyMover->setTileMap(_tileMapLayer);
    container->addChild(honeyMover);

	this->schedule(schedule_selector(GameScene::saveGameState), 60.0f);
	this->schedule(schedule_selector(GameScene::beeHiveAtlasUpdate), 1.0f);
	this->schedule(schedule_selector(GameScene::honeyExtractorAtlasUpdate), 1.0f);
	this->schedule(schedule_selector(GameScene::tutorialUpdate), 1.0f);
	this->schedule(schedule_selector(GameScene::timeUpdate), UPDATE_TIME);
	return true;
}
void GameScene::timeUpdate(float dt) {
	Time::getInstance()->update(dt);
}

void GameScene::beeHiveAtlasUpdate(float dt) {
	BeeHiveAtlas::getInstance()->updateBeeHives(dt);
}

void GameScene::honeyExtractorAtlasUpdate(float dt) {
	HoneyExtractorAtlas::getInstance()->updateHoneyExtractors(dt);
}

void GameScene::tutorialUpdate(float dt) {
	if (Time::getInstance()->getSeason() == Season::Fall) {
		auto storyScene = StoryScene::getInstance();
		UICustom::Popup* popup = storyScene->createPopup(4);
		if (popup) {
			this->getCameraContainer()->addChild(popup, 200);
		}	
	}
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    auto movement = touch->getLocation() - touch->getPreviousLocation();
    setContainerPos(container->getPosition() - movement);
}

void GameScene::setContainerPos(Vec2 pos) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto box = _tileMapLayer->getMap()->getBoundingBox().size;
    pos.x = clampf(pos.x, -50, box.width - visibleSize.width + 50);
    pos.y = clampf(pos.y, -50, box.height - visibleSize.height + 50);
    container->setPosition(pos);
}

void GameScene::onTouchEnded(Touch *touch, Event *event) {

}

void GameScene::saveGameState(float dt) {
	SaveLoad::saveEverything();
}

Node* GameScene::getCameraContainer() {
    return container;
}

