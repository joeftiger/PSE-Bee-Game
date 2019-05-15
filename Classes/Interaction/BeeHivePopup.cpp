
#include <Resources/Tiles.h>
#include <Resources/SpriteContainer.h>
#include <Game/GameScene.h>
#include "BeeHivePopup.h"
#include "HeaderFiles/DEFINITIONS.h"

void BeeHivePopup::initBackground() {
    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    auto size = visibleSize * 0.75;

    _background = Sprite::create();
	_background->setTextureRect(Rect(0, 0, size.width, size.height));    // background size
	_background->setColor(Color3B(255, 243, 190));
	_background->setAnchorPoint(Vec2(0.5, 0.5));

    this->addChild(_background, -1, "background");
}

void BeeHivePopup::initImage() {
    auto image = SpriteContainer::getInstance()->getSpriteOf(Tiles::TileGID::beehive_small_open);
	auto box = _background->getContentSize();

    image->setAnchorPoint(Vec2(0.0f, 1.0f));
    image->setPosition(box.width / 10, box.height);
	image->setScale(2.0f);
    _background->addChild(image, 1, "image");
}

void BeeHivePopup::initInfoPanel() {
    // TODO: Show labels of beehive information
    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    TTFConfig labelConfig;
    labelConfig.fontFilePath = FONT;
    labelConfig.fontSize = TEXT_SIZE_HUD;
    auto box = _background->getContentSize();

    //honey
    _honeyLabel = Label::createWithTTF(labelConfig, "0");
    _honeyLabel->enableOutline(Color4B::BLACK, 1);
    _honeyLabel->setAnchorPoint(Vec2(0, 0.5));
    _honeyLabel->setPosition(Vec2(box.width * 5 / 8, box.height * 2 / 3));
    _honeyLabel->setScale(2);
    auto honeySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::honey_glass_2d);
    honeySprite->setScale(0.3f);
    honeySprite->setAnchorPoint(Vec2(1, 0.5f));
    honeySprite->setPosition(Vec2(-30, 15));

    _background->addChild(_honeyLabel);
    _honeyLabel->addChild(honeySprite);

    //bees
    _beesLabel = Label::createWithTTF(labelConfig, "0");
    _beesLabel->enableOutline(Color4B::BLACK, 1);
    _beesLabel->setAnchorPoint(Vec2(0, 0.5));
    _beesLabel->setPosition(Vec2(box.width * 5 / 8, box.height * 5 / 9));
    _beesLabel->setScale(2);
    auto beeSprite = SpriteContainer::getInstance()->getSpriteOf(
            Sprites::erlenmeyer); //to change with a bee sprite
    beeSprite->setScale(0.3f);
    beeSprite->setAnchorPoint(Vec2(1, 0.5f));
    beeSprite->setPosition(Vec2(-30, 15));

	_background->addChild(_beesLabel);
    _beesLabel->addChild(beeSprite);

    //food
    _foodLabel = Label::createWithTTF(labelConfig, "0");
    _foodLabel->enableOutline(Color4B::BLACK, 1);
    _foodLabel->setAnchorPoint(Vec2(0, 0.5));
    _foodLabel->setPosition(Vec2(box.width * 5 / 8, box.height * 4 / 9));
    _foodLabel->setScale(2);
    auto foodSprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::erlenmeyer);
    foodSprite->setScale(0.3);
    foodSprite->setAnchorPoint(Vec2(1, 0.5));
    foodSprite->setPosition(Vec2(-30, 15));

    _background->addChild(_foodLabel);
    _foodLabel->addChild(foodSprite);

    //varroa
    _varroaLabel = Label::createWithTTF(labelConfig, "0");
    _varroaLabel->enableOutline(Color4B::BLACK, 1);
    _varroaLabel->setAnchorPoint(Vec2(0, 0.5));
    _varroaLabel->setPosition(Vec2(box.width * 5 / 8, box.height * 1 / 3));
    _varroaLabel->setScale(2);
    auto varroaSprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::honey_glass_3d);
    varroaSprite->setScale(0.3f);
    varroaSprite->setAnchorPoint(Vec2(1, 0.5f));
    varroaSprite->setPosition(Vec2(-30, 15));

	_background->addChild(_varroaLabel);
    _varroaLabel->addChild(varroaSprite);
}

void BeeHivePopup::initButtons() {
    /* TODO: Show Buttons to interact with like:
     * - takeHoney();
     * - giveSugarWater();
     * - giveMedicine();
     */
    Vector<ui::Button*> buttons;

	auto box = _background->getContentSize();

	auto takeHoney = ui::Button::create("menu/yes.png");
	takeHoney->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			
		}
	});
	takeHoney->setScale(0.3f);
	buttons.pushBack(takeHoney);

	auto giveSugarWater = ui::Button::create("menu/yes.png");
	giveSugarWater->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			_beeHive->addFood();
		}
	});
	buttons.pushBack(giveSugarWater);

	auto giveMedicine = ui::Button::create("menu/yes.png");
	giveMedicine->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			_beeHive->killVarroa();
		}
	});
	buttons.pushBack(giveMedicine);

	int index = 0;
	auto buttonSize = takeHoney->getBoundingBox().size;
	auto offset = buttonSize.width * 2.5f;
	auto basePos = Vec2(-offset, 0);
	
	
	for (ui::Button* b : buttons) {
		b->setAnchorPoint(Vec2(0, 0));
		b->setScale(0.3f);
		_background->addChild(b);
		b->setPosition(Vec2(basePos.x + (buttonSize.width * index) + offset, basePos.y));
		index++;
	}

	auto exitButton = ui::Button::create("menu/no.png");
	exitButton->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			this->removeFromParentAndCleanup(true);
		}
	});
	exitButton->setScale(0.15f);
	exitButton->setAnchorPoint(Vec2(1.0f, 1.0f));
	exitButton->setPosition(Vec2(box.width, box.height));
	_background->addChild(exitButton);

}

void BeeHivePopup::initTouch() {
    auto listener = EventListenerTouchOneByOne::create();

    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(BeeHivePopup::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _background);
}

BeeHivePopup *BeeHivePopup::createWith(BeeHive *beeHive) {
    auto popup = BeeHivePopup::create();
    popup->_beeHive = beeHive;
    popup->update(0);       // loads information. Must be here.
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

    this->schedule(schedule_selector(BeeHivePopup::update), 1);

    return true;
}

bool BeeHivePopup::onTouchBegan(Touch *touch, Event *event) {
    if (!getChildByName("background")->getBoundingBox().containsPoint(touch->getLocation())) {
        //this->removeFromParentAndCleanup(true);
    }

    return true;
}

void BeeHivePopup::update(float dt) {
    _honeyLabel->setString(stringShortener(std::to_string((int) _beeHive->rawHoney())) + "g");

    _beesLabel->setString(stringShortener(std::to_string((int) _beeHive->beesAlive())));

    _varroaLabel->setString(stringShortener(std::to_string((int) _beeHive->varroaAlive())));

    _foodLabel->setString(stringShortener(std::to_string((int) _beeHive->getFood())) + "g");
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