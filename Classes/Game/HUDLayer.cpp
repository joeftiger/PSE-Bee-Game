
#include "HUDLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"

using namespace cocos2d;

cocos2d::Layer *HUDLayer::createLayer()
{
	return HUDLayer::create();
}

bool HUDLayer::init() {

    if ( !Layer::init() )
    {
        return false;
    }

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

	//add the menu item for back to main menu
	auto label = Label::createWithTTF("Main Menu", "fonts/OpenSans-Regular.ttf", 20);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW*8, visibleRect.origin.y + onePofScreenH * 5));
	this->addChild(backMenu, 10);

	// HoneyCounter + HoneySprite
	honey = 0;
	honeyLabel = Label::createWithTTF(std::to_string(honey), "fonts/OpenSans-Regular.ttf", TEXT_SIZE_HUD);
	honeyLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8, visibleRect.origin.y + visibleRect.size.height - onePofScreenH * 5));
	this->addChild(honeyLabel, HUD_PRIORITY);
	auto honeySprite = Sprite::create("sprites/honigglas_2d.png");
	honeySprite->setScale(0.1f);
	honeySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	honeySprite->setPosition(Vec2(40, 10));
	honeyLabel->addChild(honeySprite);

	//Timer
	timePassed = 0;
	months = 0;
	years = 0;
	timeLabel = Label::createWithTTF(std::to_string(timePassed), "fonts/OpenSans-Regular.ttf", TEXT_SIZE_HUD);
	this->addChild(timeLabel, HUD_PRIORITY);
	timeLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 6, visibleRect.origin.y + visibleRect.size.height - onePofScreenH * 12));
	this->schedule(schedule_selector(HUDLayer::timer), UPDATE_TIME);

    return true;
}

void HUDLayer::timer(float dt) {
	timePassed += dt;

	if (timePassed/60 >= LENGTH_MONTH) {
		timePassed = 0;
		months++;
	}

	if (months >= LENGTH_YEAR) {
		months = 0;
		years++;
	}

	__String * timeToDisplay = __String::createWithFormat("%i", months);
	timeLabel->setString(timeToDisplay->getCString());
}