
#include "OptionsScene.h"
#include "../Settings.h"
#include "SaveDeleteConfirmation.h"
#include "MainMenu/MainMenuScene.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;


void OptionsScene::initTextureButton() {
	auto checkbox = CheckBox::create();
	checkbox->loadTextureBackGround("Sprites/SD.png");
	checkbox->loadTextureBackGroundDisabled("Sprites/SD.png");
	checkbox->loadTextureBackGroundSelected("Sprites/HD.png");
	checkbox->loadTextureFrontCross("Sprites/HD.png");
	checkbox->loadTextureFrontCrossDisabled("Sprites/SD.png");

	checkbox->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			cocos2d::log("Options:\tSwitching textures");
			auto settings = Settings::getInstance();
			auto option = Settings::SettingName::HD_Textures;
			settings->set(option, !settings->getAsBool(option));
		}
	});

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	checkbox->setAnchorPoint(Vec2(0.5, 0.5));
	checkbox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3.0f));

	checkbox->setSelected(Settings::getInstance()->getAsBool(Settings::SettingName::HD_Textures));

	this->addChild(checkbox, 10);
}

void OptionsScene::initTutorialButton() {
	// TODO
}

Scene *OptionsScene::createScene() { return OptionsScene::create(); }

// on "init" you need to initialize your instance
bool OptionsScene::init() {
	if (!Scene::init()) return false;

	// standard size related functions
	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

	// create a title and set it at the top of the screen
	auto title = Label::createWithTTF("Options", "fonts/ReemKufi-Regular.ttf", 48);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));
	this->addChild(title, 1);

    // add save deletion funcitonality
    auto resetLabel = Label::createWithTTF("Click here to reset your Save", "fonts/ReemKufi-Regular.ttf", 40);
    auto menuItemReset = MenuItemLabel::create(resetLabel);
    menuItemReset->setCallback([&](cocos2d::Ref *sender) {
        Director::getInstance()->replaceScene(SaveDeleteConfirmation::create());
    });
    auto resetMenu = Menu::create(menuItemReset, nullptr);
    resetMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 3 * title->getContentSize().height));
    this->addChild(resetMenu, 10);

    // switch between textures
    initTextureButton();





	// add the menu item for back to main menu and position it in the bottom right corner of the screen
	auto label = Label::createWithTTF("Main Menu", "fonts/ReemKufi-Regular.ttf", 20);
	auto menuItemBack = MenuItemLabel::create(label);
	menuItemBack->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItemBack, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8,
	                           visibleRect.origin.y + onePofScreenH * 5));
	this->addChild(backMenu, 10);


	return true;
}

// upon presseing the rest button, delete the save and go back to main menu
void OptionsScene::onDeleteSaveClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.2f, SaveDeleteConfirmation::create(), Color3B(255, 255, 255)));
}
