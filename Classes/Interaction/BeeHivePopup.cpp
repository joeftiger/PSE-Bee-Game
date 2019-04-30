//
// Created by julius on 30.04.19.
//

#include <Resources/Tiles.h>
#include <Resources/SpriteContainer.h>
#include "BeeHivePopup.h"

void BeeHivePopup::initBackground() {
    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    auto size = visibleSize * 0.75;

    auto background = Sprite::create();
    background->setTextureRect(Rect(0, 0, size.width, size.height));    // background size
    background->setColor(Color3B(255, 243, 190));
    background->setAnchorPoint(Vec2(0.5, 0.5));

    this->addChild(background, -1, "background");
}

void BeeHivePopup::initImage() {
    auto image = SpriteContainer::getInstance()->getSpriteOf(Tiles::TileGID::beehiveSmall2);
    auto background = this->getChildByName("background");
    auto box = background->getContentSize();

    image->setAnchorPoint(Vec2(0, 0.5));
    image->setPosition(box.width / 10, box.height * 2 / 3);
    background->addChild(image, 1, "image");
}

void BeeHivePopup::initInfoPanel() {
    // TODO: Show labels of beehive information
}

void BeeHivePopup::initButtons() {
    /* TODO: Show Buttons to interact with like:
     * - takeHoney();
     * - giveSugarWater();
     * - giveMedicine();
     */
}

void BeeHivePopup::initTouch() {
    auto listener = EventListenerTouchOneByOne::create();

    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(BeeHivePopup::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

BeeHivePopup *BeeHivePopup::createWith(BeeHive *beeHive) {
    auto popup = BeeHivePopup::create();
    popup->_beeHive = beeHive;
    return popup;
}

bool BeeHivePopup::init() {
    if (!Node::init()) return false;

    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    initBackground();
    initImage();
    initInfoPanel();
    initButtons();
    initTouch();

    return true;
}

bool BeeHivePopup::onTouchBegan(Touch *touch, Event *event) {
    if (!getChildByName("background")->getBoundingBox().containsPoint(touch->getLocation())) {
        this->removeFromParentAndCleanup(true);
    }
    return true;
}
