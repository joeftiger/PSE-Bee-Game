//
// Created by Uro on 3/30/2019.
//

#include <Resources/Tiles.h>
#include <TileMapObjects/PlaceableTile.h>
#include <Resources/Sprites.h>
#include <TileMapObjects/PlaceableSprite.h>
#include "ItemPanelLayer.h"
#include "TouchUtil.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"
#include "Game/TileMapLayer.h"

using namespace cocos2d;

LayerColor *ItemPanelLayer::createLayer() { return ItemPanelLayer::create(); }

bool ItemPanelLayer::init() {

	if (!LayerColor::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getWinSize();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ItemPanelLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ItemPanelLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ItemPanelLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//Item Panel
	this->setColor(Color3B::WHITE);
	this->setContentSize(Size(visibleSize.width / 4, visibleSize.height));
	this->setPosition(visibleSize.width, 0);
	this->setOpacity(GLubyte(90));

	//show Item Panel Layer
	_showRec = LayerColor::create(Color4B::WHITE, 40, 80);
	_showRec->setPosition(0 - 40, this->getContentSize().height / 2 - 40);
	this->addChild(_showRec);

	initializeItemPanel();

	return true;
}

void ItemPanelLayer::initializeItemPanel() {
	auto box = this->getBoundingBox().size;

	this->addToPlaceables(new PlaceableTile(Tiles::beehiveSmall1));
	this->addToPlaceables(new PlaceableTile(Tiles::beehiveMiddle1));
	this->addToPlaceables(new PlaceableTile(Tiles::beehiveBig1));
	this->addToPlaceables(new PlaceableTile(Tiles::flower1));
	this->addToPlaceables(new PlaceableTile(Tiles::flower2));
	this->addToPlaceables(new PlaceableTile(Tiles::flower3));
	this->addToPlaceables(new PlaceableTile(Tiles::flower4));
	this->addToPlaceables(new PlaceableTile(Tiles::bush1));
	this->addToPlaceables(new PlaceableTile(Tiles::road));
	this->addToPlaceables(new PlaceableSprite(Sprites::tree_1));
	this->addToPlaceables(new PlaceableSprite(Sprites::tree_2));
	this->addToPlaceables(new PlaceableSprite(Sprites::tree_4));

	this->addToSpriteList("tilemaps/Tiles/blumen1_spring_summer.png", Vec2(0, box.height / 6), Tiles::flower1, box);
	this->addToSpriteList("tilemaps/Tiles/blumen2_spring_summer.png", Vec2(box.width / 3, box.height / 6),
	                      Tiles::flower2,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/blumen3_spring_summer.png", Vec2(box.width * 2 / 3, box.height / 6),
	                      Tiles::flower3,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/blumen4_spring_summer.png", Vec2(0, box.height * 2 / 6), Tiles::flower4,
	                      box);

	this->addToSpriteList("tilemaps/Tiles/steinplattenboden.png", Vec2(box.width / 3, box.height * 2 / 6),
	                      Tiles::road, box);
	this->addToSpriteList("tilemaps/Tiles/busch1_spring_summer.png", Vec2(box.width * 2 / 3, box.height * 2 / 6),
	                      Tiles::bush1,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/busch2_spring_summer.png", Vec2(0, box.height * 3 / 6), Tiles::bush2, box);
	this->addToSpriteList("tilemaps/Tiles/busch3_spring_summer.png", Vec2(box.width / 3, box.height * 3 / 6),
	                      Tiles::bush3,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/busch4_spring_summer.png", Vec2(box.width * 2 / 3, box.height * 3 / 6),
	                      Tiles::bush4,
	                      box);

	this->addToSpriteList("tilemaps/Tiles/bienenstock1_gross.png", Vec2(0, box.height * 4 / 6), Tiles::beehiveBig1,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/bienenstock1_mittel.png", Vec2(box.width / 3, box.height * 4 / 6),
	                      Tiles::beehiveMiddle1, box);
	this->addToSpriteList("tilemaps/Tiles/bienenstock1_klein.png", Vec2(box.width * 2 / 3, box.height * 4 / 6),
	                      Tiles::beehiveSmall1, box);

	addListTo(this);
}

LayerColor *ItemPanelLayer::getShowRec() {
	return _showRec;
}

void ItemPanelLayer::setTileMap(TileMapLayer* tileMap) {
    _tileMapLayer = tileMap;
}

void ItemPanelLayer::showHideItemPanel(const Point &touchPos) {
	if (_showRec->getBoundingBox().containsPoint(touchPos - this->getPosition())) {
		if (_isItemShow) {
			MoveBy *hide = MoveBy::create(0.2, Vec2(this->getBoundingBox().size.width, 0));
			this->runAction(hide);
			_isItemShow = false;

			_tileMapLayer->showObstructions(false);
		} else {
			MoveBy *show = MoveBy::create(0.2, Vec2(-this->getBoundingBox().size.width, 0));
			this->runAction(show);
			_isItemShow = true;
			_tileMapLayer->showObstructions(true);
		}
		_isTouch = true;
	}
	if (_isItemShow) {
		touchOnItemPanel(touchPos);
	}
}

void ItemPanelLayer::touchOnItemPanel(const Point &touchPos) {
	if (this->getBoundingBox().containsPoint(touchPos)) {
		this->setDrag(touchPos, this->getPosition());
		if (isDrag()) {
			this->addChild(this->getDrag());
		}
		_isTouch = true;
	}
}

bool ItemPanelLayer::onTouchBegan(Touch *touch, Event *event) {
    _touchPosition = touch->getLocation();
    this->showHideItemPanel(_touchPosition);
    return _isTouch;
}

void ItemPanelLayer::onTouchMoved(Touch *touch, Event *event) {
    _touchPosition = touch->getLocation();


    if (isDrag()) {
        drag->setPosition(_touchPosition - this->getPosition());
    }
}

void ItemPanelLayer::onTouchEnded(void *, void *) {
    auto pos = _touchPosition + this->getParent()->getPosition();
    if (isDrag()) {
        auto gid = drag->getTag();

        if (_tileMapLayer->canPlaceTile(pos, gid)) {
            _tileMapLayer->placeTile(pos, gid);
        }

        this->removeChild(this->getDrag());
        this->setIsDrag(false);
    }
    _isTouch = false;
}