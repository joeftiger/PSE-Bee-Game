
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
        _isDrag = true;

        if(!_honeySprite) {
            _honeySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::honey_glass_2d);
            _honeySprite->setAnchorPoint(Vec2(0.5, 0));
            _honeySprite->setScale(0.2);
            _honeySprite->setVisible(false);
            this->addChild(_honeySprite);
        }

        return true;
    } else if(extractorAtlas->hasHoneyExtractorAt(pos)) {
        return true;
    }
    return false;
}

void HoneyMover::onTouchMoved(Touch *touch, Event *event) {
    if(_honeySprite) {
        _honeySprite->setPosition(Vec2(touch->getLocation()));
        _honeySprite->setVisible(true);
    }

}

void HoneyMover::onTouchEnded(Touch *touch, void *) {
    _honeySprite->setVisible(false);
    if(this->getChildByName("sprite")) {
        this->removeChildByName("sprite");
    }
    auto extractorAtlas = HoneyExtractorAtlas::getInstance();
    auto beeAtlas = BeeHiveAtlas::getInstance();
    auto pos = _tileMapLayer->getTilePosition(touch->getLocation() + this->getParent()->getPosition());
    if(extractorAtlas->hasHoneyExtractorAt(pos)) {

        _extractor = extractorAtlas->getHoneyExtractorAt(pos);
        if(_isDrag) {
            _extractor->addHoneyToExtractor(_beeHive->takeRawHoney());
        }

        auto popup = HoneyExtractorPopup::createWith(_extractor);
        this->addChild(popup, 100);

    } else if (beeAtlas->hasBeeHiveAt(pos)) {
        _beeHive = beeAtlas->getBeeHiveAt(pos);
        auto popup = BeeHivePopup::createWith(_beeHive);
        this->addChild(popup, 100);
    }
    _isDrag = false;

}

void HoneyMover::interactAt(const Vec2& pos) {

    if(BeeHiveAtlas::getInstance()->hasBeeHiveAt(pos)) {
        auto beeHive = BeeHiveAtlas::getInstance()->getBeeHiveAt(pos);
        auto popup = BeeHivePopup::createWith(beeHive);
        this->addChild(popup, 100);

    } else if(HoneyExtractorAtlas::getInstance()->hasHoneyExtractorAt(pos)) {

        auto honeyExtractor = HoneyExtractorAtlas::getInstance()->getHoneyExtractorAt(pos);
        auto popup = HoneyExtractorPopup::createWith(honeyExtractor);
        this->addChild(popup, 100);

    }
}