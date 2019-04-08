//
// Created by Uro on 3/30/2019.
//

#include <HeaderFiles/TileGID.h>
#include "ItemPanelLayer.h"
#include "Game/TouchUtil.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"

using namespace cocos2d;

LayerColor *ItemPanelLayer::createLayer() {
	return ItemPanelLayer::create();
}

bool ItemPanelLayer::init() {

	if (!LayerColor::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getWinSize();

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

	this->addToSpriteList("tilemaps/Tiles/blumen1_spring_summer.png", Vec2(0, box.height / 6), flower1, box);
	this->addToSpriteList("tilemaps/Tiles/blumen2_spring_summer.png", Vec2(box.width / 3, box.height / 6), flower2,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/blumen3_spring_summer.png", Vec2(box.width * 2 / 3, box.height / 6), flower3,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/blumen4_spring_summer.png", Vec2(0, box.height * 2 / 6), flower4, box);

	this->addToSpriteList("tilemaps/Tiles/steinplattenboden.png", Vec2(box.width / 3, box.height * 2 / 6), road, box);
	this->addToSpriteList("tilemaps/Tiles/busch1_spring_summer.png", Vec2(box.width * 2 / 3, box.height * 2 / 6), bush1,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/busch2_spring_summer.png", Vec2(0, box.height * 3 / 6), bush2, box);
	this->addToSpriteList("tilemaps/Tiles/busch3_spring_summer.png", Vec2(box.width / 3, box.height * 3 / 6), bush3,
	                      box);
	this->addToSpriteList("tilemaps/Tiles/busch4_spring_summer.png", Vec2(box.width * 2 / 3, box.height * 3 / 6), bush4,
	                      box);

	this->addToSpriteList("tilemaps/Tiles/bienenstock1_gross.png", Vec2(0, box.height * 4 / 6), beehiveBig, box);
	this->addToSpriteList("tilemaps/Tiles/bienenstock1_mittel.png", Vec2(box.width / 3, box.height * 4 / 6),
	                      beehiveMiddle, box);
	this->addToSpriteList("tilemaps/Tiles/bienenstock1_klein.png", Vec2(box.width * 2 / 3, box.height * 4 / 6),
	                      beehiveSmall, box);

	addListTo(this);
}

LayerColor *ItemPanelLayer::getShowRec() {
	return _showRec;
}

void ItemPanelLayer::showHideItemPanel(Point touchPos) {
	if (this->getShowRec()->getBoundingBox().containsPoint(touchPos - this->getPosition())) {
		if (_isItemShow) {
			MoveBy *hide = MoveBy::create(0.2, Vec2(this->getBoundingBox().size.width, 0));
			this->runAction(hide);
			_isItemShow = false;

		} else {
			MoveBy *show = MoveBy::create(0.2, Vec2(-this->getBoundingBox().size.width, 0));
			this->runAction(show);
			_isItemShow = true;
		}
	}
	if (_isItemShow) {
		touchOnItemPanel(touchPos);
	}
}

void ItemPanelLayer::touchOnItemPanel(Point touchPos) {
	if (this->getBoundingBox().containsPoint(touchPos)) {
		this->setDrag(touchPos, this->getPosition());
		if (this->isDrag()) {
			this->addChild(this->getDrag());
		}
	}
}