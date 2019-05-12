#include "HoneyExtractorPopup.h"
#include "HeaderFiles/DEFINITIONS.h"
#include <Resources/Tiles.h>
#include <Resources/SpriteContainer.h>
#include <Settings.h>
#include "ui/CocosGUI.h"
#include "Game/Player.h"

void HoneyExtractorPopup::initBackground() {
	auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
	auto size = visibleSize * 0.75;

	auto background = Sprite::create();
	background->setTextureRect(Rect(0, 0, size.width, size.height));    // background size
	background->setColor(Color3B(255, 243, 190));
	background->setAnchorPoint(Vec2(0.5, 0.5));

	this->addChild(background, -1, "background");
}

void HoneyExtractorPopup::initImage() {
	auto image = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::honey_extractor);
	auto background = this->getChildByName("background");
	auto box = background->getContentSize();

	image->setAnchorPoint(Vec2(0, 0.5));
	image->setPosition(box.width / 10, box.height * 2 / 3);
	background->addChild(image, 1, "image");
}

void HoneyExtractorPopup::initInfoPanel() {

	auto background = this->getChildByName("background");
	auto box = background->getContentSize();

	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT;
	labelConfig.fontSize = TEXT_SIZE_HUD;

	_honeyLabel = Label::createWithTTF(labelConfig, "0");
	_honeyLabel->enableOutline(Color4B::BLACK, 1);
	_honeyLabel->setAnchorPoint(Vec2(0, 0.5));
	_honeyLabel->setPosition(Vec2(box.width * 5 / 8, box.height * 2 / 3));
	_honeyLabel->setScale(2);

	auto honeySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::honey_glass_2d);
	honeySprite->setScale(0.1f);
	honeySprite->setAnchorPoint(Vec2(1, 0.5f));
	honeySprite->setPosition(Vec2(-30, 15));

	background->addChild(_honeyLabel);
	_honeyLabel->addChild(honeySprite);
}

void HoneyExtractorPopup::initButtons() {
	auto background = this->getChildByName("background");
	auto box = background->getContentSize();

	auto closeButton = ui::Button::create("menu/no.png");

	closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			this->removeFromParentAndCleanup(true);
			break;
		}
	});
	closeButton->setScale(0.2f);
	closeButton->setPosition(Vec2(box.width * 0.9f, box.height * 0.9f));

	background->addChild(closeButton);

	auto addHoneyButton = ui::Button::create("menu/yes.png");

	addHoneyButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//TODO: Add honey
			break;
		}
	});

	addHoneyButton->setScale(0.2f);
	addHoneyButton->setPosition(Vec2(box.width * 0.1f, box.height * 0.1f));
	background->addChild(addHoneyButton);
}

void HoneyExtractorPopup::initTouch() {
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HoneyExtractorPopup::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getChildByName("background"));
}

void HoneyExtractorPopup::update(float dt) {
	_honeyLabel->setString(std::to_string((int)_honeyExtractor->honeyInExtractor()));
}

HoneyExtractorPopup * HoneyExtractorPopup::createWith(HoneyExtractor * honeyExtractor) {
	auto popup = HoneyExtractorPopup::create();
	popup->_honeyExtractor = honeyExtractor;
	popup->update(0);
	return popup;
}

bool HoneyExtractorPopup::init() {
	if (!Node::init()) return false;

	auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	initBackground();
	initImage();
	initButtons();
	initTouch();
	initInfoPanel();

	this->schedule(schedule_selector(HoneyExtractorPopup::update), 1);

	return true;
}

bool HoneyExtractorPopup::onTouchBegan(Touch * touch, Event * event) {
	return true;
}
