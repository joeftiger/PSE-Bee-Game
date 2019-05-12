
#include "HUDLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"
#include "Player.h"
#include "SaveLoad/SaveLoad.h"
#include "Story/StoryScene.h"
#include "Resources/SpriteContainer.h"

using namespace cocos2d;

Layer *HUDLayer::createLayer() { 	return HUDLayer::create(); }

bool HUDLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

	//create label configuration, can be reused in all labels
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT;
	labelConfig.fontSize = TEXT_SIZE_HUD;

	//add the menu item for back to main menu
	auto label = Label::createWithTTF(labelConfig, "Main Menu");
	label->enableOutline(Color4B::BLACK, 1);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		SaveLoad::saveEverything();
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8,
	                           visibleRect.origin.y + onePofScreenH * 5));
	this->addChild(backMenu, 10);

	// HoneyCounter + HoneySprite
	honey = 0;
	honeyLabel = Label::createWithTTF(labelConfig, std::to_string(honey));
	honeyLabel->enableOutline(Color4B::BLACK, 1);
	honeyLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 20,
	                             visibleRect.origin.y + visibleRect.size.height - onePofScreenH * 5));
	this->addChild(honeyLabel, HUD_PRIORITY);
	auto honeySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::honey_glass_2d);
	honeySprite->setScale(0.5f);
	honeySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	honeySprite->setPosition(Vec2(-30, 15));
	honeyLabel->addChild(honeySprite);

	//MoneyCounter + MoneySprite
	money = 0;
	moneyLabel = Label::createWithTTF(labelConfig, std::to_string(honey));
	moneyLabel->enableOutline(Color4B::BLACK, 1);
	moneyLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 11,
	                             visibleRect.origin.y + visibleRect.size.height - onePofScreenH * 5));
	this->addChild(moneyLabel, HUD_PRIORITY);
	auto moneySprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::coin_single);
	moneySprite->setScale(0.5f);
	moneySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	moneySprite->setPosition(Vec2(-30, 15));
	moneyLabel->addChild(moneySprite);

	//Timer

	timeLabel = Label::createWithTTF(labelConfig, std::to_string(Time::getInstance()->getMonth()));
	timeLabel->enableOutline(Color4B::BLACK, 1);
	this->addChild(timeLabel, HUD_PRIORITY);
	timeLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 5,
	                            visibleRect.origin.y + visibleRect.size.height - onePofScreenH * 5));
	this->schedule(schedule_selector(HUDLayer::timer), 0.1f);

    //UICustom::Popup *popup = UICustom::Popup::createAsMessage("GROSSVATER", "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...");
    //this->addChild(popup);
    //auto storyScene = StoryScene::create();
    //this->addChild(storyScene, 50);
    auto storyScene = StoryScene::create();
    UICustom::Popup* popup = storyScene->createPopup(0);
    this->addChild(popup);

	return true;
}

/**

*/
void HUDLayer::timer(float dt) {

	auto h = std::to_string((int) Player::getInstance()->totalRawHoney());
	honeyLabel->setString(stringShortener(h) + "g");

	auto m = std::to_string((int) Player::getInstance()->returnTotalMoney());
	moneyLabel->setString(stringShortener(m));

	timeLabel->setString(Time::getInstance()->getMonthAsString());
}

/**
	Abbreviates string if it is longer than 4 Digits
	@param s string to be shortened
	@return shortened string
*/
std::string HUDLayer::stringShortener(std::string s) {
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