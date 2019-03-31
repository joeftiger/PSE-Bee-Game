
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "HeaderFiles/TileGID.h"
#include "SaveLoad/SaveLoad.h"
#include "ItemPanelLayer.h"
#include "AppDelegate.h"


using namespace cocos2d;

Layer* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Layer::init()) return false;

	Size visibleSize = Director::getInstance()->getWinSize();

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
	_tileMapLayer->setPosition(Vec2(-_tileMapLayer->getMap()->getBoundingBox().size.width/2, -_tileMapLayer->getMap()->getBoundingBox().size.height/2));

    // TileMapAtlas and observe TileMap
    auto tileMapAtlas = BeeHiveAtlas::getInstance();
	_tileMapLayer->subscribe(tileMapAtlas);

	//HUD Layer
	_HUDLayer = HUDLayer::create();
	this->addChild(_HUDLayer);

    //Item Panel Layer
	_itemPanel = ItemPanelLayer::create();
	_itemPanel->initializeItemPanel(this);
    addListTo(_itemPanel);
    this->addChild(_itemPanel);

    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	_isTouched = true;
	_touchPosition = touch->getLocation();
	ShowHideItemPanel();
	if(_isItemShow) {
        touchOnItemPanel();
	}
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
	auto touchPos = touch->getLocation();
	auto movement = touchPos - _touchPosition;
	_touchPosition = touchPos;


	if (_isDrag) {
		drag->setPosition(touchPos - cameraTravel);
	}
	else {
	    cameraTravel += movement;
		camera->setPosition(camera->getPosition() - movement);
		_HUDLayer->setPosition(_HUDLayer->getPosition() - movement);
        _itemPanel->setPosition(_itemPanel->getPosition() - movement);
	}
    
}

void GameScene::onTouchEnded(void *, void *) {
	if (_isDrag) {
		_tileMapLayer->setTile(_touchPosition - cameraTravel - _tileMapLayer->getPosition(), drag->getTag());
		this->removeChild(drag);
		_isDrag = false;
	}
	_isTouched = false;
	_isDrag = false;
	_touchPosition = Point(0, 0);
}

void GameScene::touchOnItemPanel() {
    if(_itemPanel->getBoundingBox().containsPoint(_touchPosition - cameraTravel)) {
        setDrag(_touchPosition - cameraTravel, _itemPanel->getPosition());
        if(_isDrag){
            this->addChild(drag);
        }
    }
}

void GameScene::ShowHideItemPanel() {
    if(_itemPanel->getShowRec()->getBoundingBox().containsPoint(_touchPosition - cameraTravel - _itemPanel->getPosition())) {
        if(_isItemShow) {
            MoveBy *hide = MoveBy::create(0.2, Vec2(_itemPanel->getBoundingBox().size.width, 0));
            _itemPanel->runAction(hide);
            _isItemShow = false;

        } else {
            MoveBy *show = MoveBy::create(0.2, Vec2(-_itemPanel->getBoundingBox().size.width, 0));
            _itemPanel->runAction(show);
            _isItemShow = true;
        }
    }
}

void GameScene::setCamera(Camera *c) {
    camera = c;
}


