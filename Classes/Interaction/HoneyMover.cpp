//
// Created by uro on 5/1/19.
//

#include <Atlas/HoneyExtractorAtlas.h>
#include <Atlas/BeeHiveAtlas.h>
#include <Resources/SpriteContainer.h>
#include "HoneyMover.h"

#include "cocos2d.h"
#include "Game/GameScene.h"
#include "BeeHivePopup.h"
#include "HoneyExtractorPopup.h"

Node *HoneyMover::createNode() {return HoneyMover::create();}

bool HoneyMover::init() {
    if(!Node::init()) {
        return false;
    }

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HoneyMover::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HoneyMover::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HoneyMover::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    _honeySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::honey_glass_2d);
    _honeySprite->setAnchorPoint(Vec2(0.5, 0));


    return true;
}

void HoneyMover::setTileMap(TileMapLayer* tileMap) {
    _tileMapLayer = tileMap;
}

bool HoneyMover::onTouchBegan(Touch *touch, Event *event) {
    auto beeAtlas = BeeHiveAtlas::getInstance();
    auto extractorAtlas = HoneyExtractorAtlas::getInstance();
    auto pos = _tileMapLayer->getTilePosition(touch->getLocation() + this->getParent()->getPosition());
    if(beeAtlas->hasBeeHiveAt(pos)) {
        _beeHive = beeAtlas->getBeeHiveAt(pos);

        auto sprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::honey_glass_2d);

        sprite->setPosition(touch->getLocation());
        sprite->setAnchorPoint(Vec2(0.5, 0));
        sprite->setScale(0.2);
        this->addChild(sprite, HUD_PRIORITY, "sprite");

        return true;
    } else if(extractorAtlas->hasHoneyExtractorAt(pos)) {
        return true;
    }
    return false;
}

void HoneyMover::onTouchMoved(Touch *touch, Event *event) {
    if(this->getChildByName("sprite")) {
        this->getChildByName("sprite")->setPosition(Vec2(touch->getLocation()));
    }

}

void HoneyMover::onTouchEnded(Touch *touch, void *) {
    auto extractorAtlas = HoneyExtractorAtlas::getInstance();
    auto beeAtlas = BeeHiveAtlas::getInstance();
    auto pos = _tileMapLayer->getTilePosition(touch->getLocation() + this->getParent()->getPosition());
    if(extractorAtlas->hasHoneyExtractorAt(pos)) {

        _extractor = extractorAtlas->getHoneyExtractorAt(pos);
        _extractor->addHoneyToExtractor(_beeHive->takeRawHoney());
        interactAt(pos);
    } else if (beeAtlas->hasBeeHiveAt(pos)) {
        interactAt(pos);
    }
    if(this->getChildByName("sprite")) {
        this->removeChildByName("sprite");
    }

}

void HoneyMover::interactAt(const Vec2& pos) {

    if(BeeHiveAtlas::getInstance()->hasBeeHiveAt(pos)) {
        auto beeHive = BeeHiveAtlas::getInstance()->getBeeHiveAt(pos);
        auto popup = BeeHivePopup::createWith(beeHive);
        this->addChild(popup, 100);

//        auto beeHive = BeeHiveAtlas::getInstance()->getBeeHiveAt(selectTilePos);
//        Interacter *i = Interacter::create();
//        this->addChild(i, 100);
//        i->runWith(beeHive);
//        i->interact();

    } else if(HoneyExtractorAtlas::getInstance()->hasHoneyExtractorAt(pos)) {

        auto honeyExtractor = HoneyExtractorAtlas::getInstance()->getHoneyExtractorAt(pos);
        auto popup = HoneyExtractorPopup::createWith(honeyExtractor);
        this->addChild(popup, 100);

        /*
        auto honeyExtractor = HoneyExtractorAtlas::getInstance()->getHoneyExtractorAt(selectTilePos);
        Interacter *i = Interacter::create();
        this->addChild(i, 100);
        i->runWith(honeyExtractor);
        i->interact();
        */
    }
}