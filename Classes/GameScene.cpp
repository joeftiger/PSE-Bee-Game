
#include "GameScene.h"
#include "BeeHiveAtlas.h"

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
	_tileMapLayer->subscribe(tileMapAtlas);

	//HUD Layer
	_HUDLayer = HUDLayer::create();
	this->addChild(_HUDLayer);

	//place plant
	flower = Sprite::create("sprites/blumen1_spring_summer.png");
	flower->setScale(0.1f);
	flower->setAnchorPoint(Vec2(0.5f, 0.5f));
	flower->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - 40, visibleRect.origin.y + 400));
	this->addChild(flower, HUD_PRIORITY);

    return true;
}

void GameScene::placeFlower(Sprite *flower) {
	if (flower->getBoundingBox().containsPoint(_touchPosition))
	{
		auto name = flower->getResourceName();
		_isDrag = true;
		drag = Sprite::create(name);
		drag->setScale(MAP_SCALE / 2);
		drag->setAnchorPoint(Vec2(0.5f, 0.5f));
		_tileMapLayer->addChild(drag, HUD_PRIORITY);
	}
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	_isTouched = true;
	_touchPosition = touch->getLocation();
	placeFlower(flower);
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
	auto touchPos = touch->getLocation();
	auto movement = touchPos - _touchPosition;
	auto finalPos = _tileMapLayer->getPosition() + movement;
	_touchPosition = touchPos;

	if (_isDrag) {
		drag->setPosition(touchPos - _tileMapLayer->getPosition());
		drag->setLocalZOrder(_tileMapLayer->getContentSize().height * 4 - drag->getPositionY()); //sperimental way to give the right priority
	}
	else {
		_tileMapLayer->setPosition(finalPos);
	}
    
}

void GameScene::onTouchEnded(void *, void *) {
	if (_isDrag) {
		_tileMapLayer->setTile(_touchPosition - _tileMapLayer->getPosition(), 1);
		_tileMapLayer->removeChild(drag);
		_isDrag = false;
	}
	_isTouched = false;
	_isDrag = false;
	_touchPosition = Point(0, 0);
}


