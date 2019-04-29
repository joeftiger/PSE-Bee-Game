//
// Created by uro on 4/28/19.
//

#include "InteractionNode.h"
#include "cocos2d.h"

using namespace cocos2d;

Node *InteractionNode::createNode() { return InteractionNode::create(); }

bool InteractionNode::init() {

    if (!Node::init()) {
        return false;
    }

	this->setUpTouches();

    return true;
}

void InteractionNode::setFiles(std::string itemName, std::string backgroundName) {
    _itemName = itemName;
    _backgroundName = backgroundName;
}

void InteractionNode::runAnimation() {

    Size winSize = Director::getInstance()->getWinSize();
    _background = Sprite::create("menu/main-menu-background.png"); //background sprite
    _background->setOpacity(0);
    _background->setAnchorPoint(Vec2(0.5,0.5));
    _background->setPosition(Vec2(winSize.width/2, winSize.height/2));
    FadeTo *fade = FadeTo::create(0.2, 120);

    this->addChild(_background, -1);
    _background->runAction(fade);

    _item = Sprite::create("tilemaps/Tiles/bienenstock1_klein.png");
    _item->setAnchorPoint(Vec2(0.5, 0.5));
    _item->setPosition(Vec2(winSize.width/2, winSize.height/2));
    _item->setScale(0.1);

    ScaleBy *scale = ScaleBy::create(0.2, 10);
    this->addChild(_item);
    _item->runAction(scale);

}

void InteractionNode::setUpTouches() {
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		if (_background) {
			if (!_background->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation()))) {
				this->removeFromParentAndCleanup(true);
			}
		}
		else {
			this->removeFromParentAndCleanup(true);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}