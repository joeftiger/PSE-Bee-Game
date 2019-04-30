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
    background->setColor(Color3B(lround(87.5), lround(65.9), 49));      // orange on beehive's front left.
    background->setAnchorPoint(Vec2(0.5, 0.5));

    this->addChild(background, -1, "background");
}

void BeeHivePopup::initImage() {
    auto image = SpriteContainer::getInstance()->getSpriteOf(Tiles::TileGID::beehiveSmall2);
    auto box = this->getChildByName("background")->getContentSize();

    image->setAnchorPoint(Vec2(0, 0.5));
    image->setPosition(box.width / 10, box.height / 2);
    this->addChild(image, 1, "image");
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

    return true;
}
