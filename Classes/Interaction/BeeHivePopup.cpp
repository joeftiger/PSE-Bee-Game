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

	auto box = this->getChildByName("background")->getContentSize();

	MenuItemImage *takeHoney = MenuItemImage::create("menu/yes.png", "menu/yes.png", [=](Ref *sender) {
		cocos2d::log("%s", "take honey");
		_beeHive->takeRawHoney();
		});

	MenuItemImage *giveSugarWater = MenuItemImage::create("menu/yes.png", "menu/yes.png", [=](Ref *sender) {
		cocos2d::log("%s", "give sugar");
		});

	MenuItemImage *giveMedicine = MenuItemImage::create("menu/yes.png", "menu/yes.png", [=](Ref *sender) {
		cocos2d::log("%s", "give medicine");
		});

	Vector<MenuItem*> buttons;

	buttons.pushBack(takeHoney);
	buttons.pushBack(giveSugarWater);
	buttons.pushBack(giveMedicine);
	Menu *menu = Menu::createWithArray(buttons);
	this->addChild(menu, 10, "buttonMenu");
	menu->alignItemsHorizontally();
	menu->setScale(0.3f);
	menu->setPosition(Vec2(-box.width * 5 / 7, -box.height* 4/5));

	MenuItemImage *closeButton = MenuItemImage::create("menu/no.png", "menu/no.png", [=](Ref *sender) {
		cocos2d::log("%s", "exit");		
		this->removeFromParentAndCleanup(true);
	});

	Vector<MenuItem*> exitButton;
	exitButton.pushBack(closeButton);
	Menu *exitMenu = Menu::createWithArray(exitButton);
	exitMenu->setAnchorPoint(Vec2(1.0f, 1.0f));
	exitMenu->setPosition(Vec2(-box.width * 5 / 7, -box.height* 4/5));
	exitMenu->setScale(0.2f);
	this->addChild(exitMenu, 10, "exitMenu");
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
        //this->removeFromParentAndCleanup(true);
    }

    return true;
}
