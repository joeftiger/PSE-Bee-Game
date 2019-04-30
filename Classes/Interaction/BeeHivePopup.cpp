//
// Created by julius on 30.04.19.
//

#include <Resources/Tiles.h>
#include <Resources/SpriteContainer.h>
#include "BeeHivePopup.h"
#include "HeaderFiles/DEFINITIONS.h"

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
    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    TTFConfig labelConfig;
    labelConfig.fontFilePath = FONT;
    labelConfig.fontSize = TEXT_SIZE_HUD;
    auto background = this->getChildByName("background");
    auto box = background->getContentSize();


    //honey
    _honeyLabel = Label::createWithTTF(labelConfig, "");
    _honeyLabel->enableOutline(Color4B::BLACK, 1);
    _honeyLabel->setAnchorPoint(Vec2(0, 0.5));
    _honeyLabel->setPosition(Vec2(box.width*5/8, box.height*2/3));
    _honeyLabel->setScale(2);
    auto honeySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::honey_glass_2d);
    honeySprite->setScale(0.1f);
    honeySprite->setAnchorPoint(Vec2(1, 0.5f));
    honeySprite->setPosition(Vec2(-30, 15));


    //bees
    _beesLabel = Label::createWithTTF(labelConfig, "");
    _beesLabel->enableOutline(Color4B::BLACK, 1);
    _beesLabel->setAnchorPoint(Vec2(0, 0.5));
    _beesLabel->setPosition(Vec2(box.width*5/8, box.height/2));
    _beesLabel->setScale(2);
    auto beeSprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::erlenmeyer); //to change with a bee sprite
    beeSprite->setScale(0.1f);
    beeSprite->setAnchorPoint(Vec2(1, 0.5f));
    beeSprite->setPosition(Vec2(-30, 15));

    //varroa
    _varroaLabel = Label::createWithTTF(labelConfig, "");
    _varroaLabel->enableOutline(Color4B::BLACK, 1);
    _varroaLabel->setAnchorPoint(Vec2(0, 0.5));
    _varroaLabel->setPosition(Vec2(box.width*5/8, box.height*1/3));
    _varroaLabel->setScale(2);
    auto varroaSprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::honey_glass_3d);
    varroaSprite->setScale(0.1f);
    varroaSprite->setAnchorPoint(Vec2(1, 0.5f));
    varroaSprite->setPosition(Vec2(-30, 15));


    background->addChild(_honeyLabel);
    _honeyLabel->addChild(honeySprite);
    background->addChild(_beesLabel);
    _beesLabel->addChild(beeSprite);
    background->addChild(_varroaLabel);
    _varroaLabel->addChild(varroaSprite);
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
    popup->schedule(schedule_selector(BeeHivePopup::timer), 0.1f);
    return popup;
}

bool BeeHivePopup::init() {
    if (!Node::init()) return false;

    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    initBackground();
    initImage();
    initButtons();
    initTouch();
    initInfoPanel();

    return true;
}

bool BeeHivePopup::onTouchBegan(Touch *touch, Event *event) {
    if (!getChildByName("background")->getBoundingBox().containsPoint(touch->getLocation())) {
        //this->removeFromParentAndCleanup(true);
    }

    return true;
}

void BeeHivePopup::timer(float dt) {
    _honeyLabel->setString(stringShortener(std::to_string((int) _beeHive->rawHoney())) + "g");

    _beesLabel->setString(stringShortener(std::to_string((int) _beeHive->beesAlive())));

    _varroaLabel->setString(stringShortener(std::to_string((int) _beeHive->varoaAlive())));
}

std::string BeeHivePopup::stringShortener(std::string s) {
    std::string temp;

    switch (s.length()) {
        case 4:
            temp = s.substr(0, 1);
            temp += '.';
            temp += s.substr(1, 1);
            temp += 'k';
            return temp;

        case 5:
            temp = s.substr(0, 2);
            temp += '.';
            temp += s.substr(2, 1);
            temp += 'k';
            return temp;

        case 6:
            temp = s.substr(0, 3);
            temp += 'k';
            return temp;

        case 7:
            temp = s.substr(0, 1);
            temp += '.';
            temp += s.substr(1, 1);
            temp += 'm';
            return temp;

        case 8:
            temp = s.substr(0, 2);
            temp += '.';
            temp += s.substr(2, 1);
            temp += 'm';
            return temp;

        case 9:
            temp = s.substr(0, 3);
            temp += 'm';
            return temp;

        case 10:
            temp = "stop playing already";
            return temp;

        default:
            return s;
    }
}