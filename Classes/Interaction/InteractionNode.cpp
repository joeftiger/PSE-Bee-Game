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

    Size winSize = Director::getInstance()->getWinSize();
    Sprite *bg = Sprite::create("menu/main-menu-background.png"); //background sprite
    bg->setOpacity(0);
    bg->setAnchorPoint(Vec2(0.5,0.5));
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));

    
    this->addChild(bg, -1);

    Sprite* sprite = Sprite::create("tilemaps/Tiles/bienenstock1_klein.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(Vec2(winSize.width/2, winSize.height/2));
    sprite->setScale(0.1);

    ScaleBy *scale = ScaleBy::create(0.2, 10);
    this->addChild(sprite);
    sprite->runAction(scale);

    return true;
}

void InteractionNode::initializeInteractionItem(std::string name) {

    Size winSize = Director::getInstance()->getWinSize();
    Sprite* sprite = Sprite::create(name);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(Vec2(winSize.width/2, winSize.height/2));
}