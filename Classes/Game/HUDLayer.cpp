
#include "HUDLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"
#include "Player.h"
#include "SaveLoad/SaveLoad.h"

using namespace cocos2d;

cocos2d::Layer *HUDLayer::createLayer() {
	return HUDLayer::create();
}

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
		SaveLoad::saveMap();
		SaveLoad::saveBeehives();
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
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
	auto honeySprite = Sprite::create("sprites/honigglas_2d.png");
	honeySprite->setScale(0.1f);
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
	auto moneySprite = Sprite::create("sprites/muenze_einzeln.png");
	moneySprite->setScale(0.1f);
	moneySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	moneySprite->setPosition(Vec2(-30, 15));
	moneyLabel->addChild(moneySprite);

	//Timer
	timePassed = 0;
	months = 0;
	years = 0;
	timeLabel = Label::createWithTTF(labelConfig, std::to_string(timePassed));
	timeLabel->enableOutline(Color4B::BLACK, 1);
	this->addChild(timeLabel, HUD_PRIORITY);
	timeLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 5,
	                            visibleRect.origin.y + visibleRect.size.height - onePofScreenH * 5));
	this->schedule(schedule_selector(HUDLayer::timer), UPDATE_TIME);

	return true;
}

/**

*/
void HUDLayer::timer(float dt) {
	timePassed += dt;

	if (timePassed / 60 >= LENGTH_MONTH) {
		timePassed = 0;
		months++;
	}

	if (months >= LENGTH_YEAR) {
		months = 0;
		years++;
	}
	
	auto h = std::to_string((int) Player::getInstance()->totalRawHoney());
	honeyLabel->setString(stringShortener(h));
	
	__String *timeToDisplay = __String::createWithFormat("%i", months);
	timeLabel->setString(timeToDisplay->getCString());
}
/**
	Abbriviates string if longer than 4 Digits
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