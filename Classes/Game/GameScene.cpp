
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "HeaderFiles/TileGID.h"
#include "ItemPanelLayer.h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init()) return false;

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    visibleSize = visibleRect.size;
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
	_tileMapLayer->setPosition(Vec2(visibleRect.origin.x - visibleSize.width, visibleRect.origin.y - visibleSize.height));

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

void GameScene::touchOnItemPanel() {
    if(_itemPanel->getBoundingBox().containsPoint(_touchPosition)) {
        setDrag(_touchPosition, _itemPanel->getPosition());
        if(_isDrag){
            this->addChild(drag);
        }
    }
}

void GameScene::ShowHideItemPanel() {
    if(_itemPanel->getShowRec()->getBoundingBox().containsPoint(_touchPosition - _itemPanel->getPosition())) {
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


