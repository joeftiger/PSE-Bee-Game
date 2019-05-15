
#include <Resources/Tiles.h>
#include <Resources/SpriteContainer.h>
#include <Game/GameScene.h>
#include "BeeHivePopup.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "Game/Prices.h"

void BeeHivePopup::initBackground() {
    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    auto size = visibleSize * 0.75;

    _background = Sprite::create("menu/background.png");
	_background->setTextureRect(Rect(0, 0, size.width, size.height));    // background size
	_background->setAnchorPoint(Vec2(0.5, 0.5));

    this->addChild(_background, -1, "background");
}

void BeeHivePopup::initImage() {
    auto image = SpriteContainer::getInstance()->getSpriteOf(Tiles::TileGID::beehive_small_open);
	auto box = _background->getContentSize();

    image->setAnchorPoint(Vec2(0.0f, 1.0f));
    image->setPosition(box.width / 10, box.height);
	image->setScale(1.5f);
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
    auto beeSprite = Sprite::create("mascot.png"); // TODO: change with a bee sprite
    beeSprite->setScale(0.1f);
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
    auto varroaSprite = Sprite::create("sprites/mites.png"); // TODO: change with a varroa sprite
    varroaSprite->setScale(0.03f);
    varroaSprite->setAnchorPoint(Vec2(1, 0.5f));
    varroaSprite->setPosition(Vec2(-30, 15));

	_background->addChild(_varroaLabel);
    _varroaLabel->addChild(varroaSprite);
}

void BeeHivePopup::initButtons() {

	auto box = _background->getContentSize();

	Vector<ui::Button*> buttons;

	//SugarButton
	auto giveSugarWater = ui::Button::create("menu/empty.png");
	giveSugarWater->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			_beeHive->addFood();
		}
	});
	std::string textSugar = "Zuckerwasser\n";
	textSugar += std::to_string(Prices::getPriceForSugarWater()) + " CHF";
	giveSugarWater->setTitleText(textSugar);
	giveSugarWater->setTitleAlignment(TextHAlignment::CENTER);
	giveSugarWater->setTitleFontName(FONT);
	giveSugarWater->setTitleFontSize(TEXT_SIZE_HUD);
	
	buttons.pushBack(giveSugarWater);

	//MedicineButton
	auto giveMedicine = ui::Button::create("menu/empty.png");
	giveMedicine->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			_beeHive->killVarroa();
			if (_beeHive->isDead()) {

			}
		}
	});
	buttons.pushBack(giveMedicine);

	std::string textMedicine = "Medizin\n";
	textMedicine += std::to_string(Prices::getPriceForMedicine()) + " CHF";
	giveMedicine->setTitleText(textMedicine);
	giveMedicine->setTitleAlignment(TextHAlignment::CENTER);
	giveMedicine->setTitleFontName(FONT);
	giveMedicine->setTitleFontSize(TEXT_SIZE_HUD);

	auto buttonSize = giveSugarWater->getBoundingBox().size;
	auto offsetX = buttonSize.width / 5;
	auto offsetY = buttonSize.height / 4;
	
	giveSugarWater->setPosition(Vec2(offsetX, offsetX));
	giveMedicine->setPosition(Vec2(buttonSize.width + offsetX * 2, offsetX));

	for (ui::Button* b : buttons) {
		b->setAnchorPoint(Vec2(0, 0));
		_background->addChild(b);
	}

	//ExitButton
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
	

	//ReviveButton
	if (_beeHive->isDead()) {
		auto reviveButton = ui::Button::create("menu/empty.png");
		reviveButton->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				_beeHive->revive();
				this->removeFromParentAndCleanup(true);
			}
		});
		reviveButton->setAnchorPoint(Vec2(1.0f, 0.0f));
		reviveButton->setPosition(Vec2(box.width - offsetX, offsetX));
		std::string text = "Neubevoelkerung\n" + std::to_string(Prices::getPriceForRevive()) + " CHF";
		reviveButton->setTitleAlignment(TextHAlignment::CENTER);
		reviveButton->setTitleText(text);
		reviveButton->setTitleFontName(FONT);
		reviveButton->setTitleFontSize(TEXT_SIZE_HUD);
		_background->addChild(reviveButton);
	}
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
	popup->initButtons(); //Called here, so we can create ReviveButton depending on healthstate of beeHive
    return popup;
}

bool BeeHivePopup::init() {
    if (!Node::init()) return false;

    auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    initBackground();
    initImage();
    //initButtons();
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
            temp = "Stop playing already";
            return temp;

        default:
            return s;
    }
}