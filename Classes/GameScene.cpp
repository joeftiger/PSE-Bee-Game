
#include "GameScene.h"
#include "DEFINITIONS.h"
#include "HUDLayer.h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init()) return false;

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Touch Event Listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Background TileMap
    _tileMapLayer = TileMapLayer::create();
    this->addChild(_tileMapLayer, -1);

	//HUD Layer
	_HUDLayer = HUDLayer::create();
	this->addChild(_HUDLayer);

    return true;
}

Vec2 GameScene::getClosestTile(Vec2 t)
{
	auto map = _tileMapLayer->getMap();
	auto background = map->getLayer("background");

	auto t1 = _tileMapLayer->convertToNodeSpace(t);

	Vec2 closestTile = Vec2(0, 0);
	float minDistance = 10000000;
	int x, y;
	for (x = 0; x <= 7; x++) {
		for (y = 0; y <= 7; y++) {
			auto temp = background->getTileAt(Vec2(x, y));
			auto e = temp->getPosition();
			auto tilePos = _tileMapLayer->convertToNodeSpace(e);
			float distance = sqrtf(pow(tilePos.x - t1.x , 2) + pow(tilePos.y - t1.y, 2));
			if (distance < minDistance) {
				closestTile = Vec2(x, y);
				minDistance = distance;
			}
		}
	}

	return background->getTileAt(closestTile)->getPosition();
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    _isTouched = true;
    _touchPosition = touch->getLocation();

    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    auto touchPos = touch->getLocation();
    auto movement = touchPos - _touchPosition;
    auto finalPos = _tileMapLayer->getPosition() + movement;

    _tileMapLayer->setPosition(finalPos);

    this->onTouchBegan(touch, event);
}

void GameScene::onTouchEnded(void *, void *) {
    _isTouched = false;
    _touchPosition = Point(0, 0);
}


