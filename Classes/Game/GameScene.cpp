
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "HeaderFiles/TileGID.h"

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
	_tileMapLayer->setPosition(Vec2(visibleRect.origin.x - visibleRect.size.width, visibleRect.origin.y - visibleRect.size.height));

    // TileMapAtlas and observe TileMap
    auto tileMapAtlas = BeeHiveAtlas::getInstance();
	_tileMapLayer->subscribe(tileMapAtlas);

	//HUD Layer
	_HUDLayer = HUDLayer::create();
	this->addChild(_HUDLayer);


	//initialize sprites to drag, we may want to make buttons some day;
    addToSpriteList("sprites/blumen1_spring_summer.png", Vec2(visibleRect.size.width*4/5, visibleRect.size.height/2), flower);
    addToSpriteList("sprites/busch1_spring_summer.png", Vec2(visibleRect.size.width*4/5, visibleRect.size.height/4), bush1);
    addToSpriteList("sprites/busch2_spring_summer.png", Vec2(visibleRect.size.width*4/5, visibleRect.size.height*3/4), bush2);
    addToSpriteList("sprites/busch3_spring_summer.png", Vec2(visibleRect.size.width*4/5, visibleRect.size.height*0/4), bush3);
    addToSpriteList("sprites/busch4_spring_summer.png", Vec2(visibleRect.size.width*3/5, visibleRect.size.height*3/4), bush4);
    addToSpriteList("sprites/steinplattenboden.png", Vec2(visibleRect.size.width*2/5, visibleRect.size.height*3/4), road);

    addListTo(this);

    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	_isTouched = true;
	_touchPosition = touch->getLocation();
	getDrag(_touchPosition);
	if(_isDrag){
	    this->addChild(drag);
	}
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
	auto touchPos = touch->getLocation();
	auto movement = touchPos - _touchPosition;
	auto finalPos = _tileMapLayer->getPosition() + movement;
	_touchPosition = touchPos;

	if (_isDrag) {
		drag->setPosition(touchPos);
	}
	else {
		_tileMapLayer->setPosition(finalPos);
	}
    
}

void GameScene::onTouchEnded(void *, void *) {
	if (_isDrag) {
		_tileMapLayer->setTile(_touchPosition - _tileMapLayer->getPosition(), drag->getTag());
		this->removeChild(drag);
		_isDrag = false;
	}
	_isTouched = false;
	_isDrag = false;
	_touchPosition = Point(0, 0);
}


