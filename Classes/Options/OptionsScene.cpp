//
// Created by brian on 25/03/2019.
//

#include "OptionsScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scene *OptionsScene::createScene() { return OptionsScene::create(); }

// on "init" you need to initialize your instance
bool OptionsScene::init() {
	if (!Scene::init()) return false;

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

	// Create a title to identify
	auto title = Label::createWithTTF("Options", "fonts/ReemKufi-Regular.ttf", 48);

	// position the label on the top center of the screen
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(title, 1);

	// Create a title to identify
	auto optionsText = Label::createWithTTF("Use SD Textures? (Not implemented yet)", "fonts/ReemKufi-Regular.ttf",
	                                           24);

	// position the label above the check box
	optionsText->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                                 origin.y + 40 + 0.5 * visibleSize.height - title->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(optionsText, 1);

	//add the menu item for delete savemenu
    auto labelDelete = Label::createWithTTF("Click to Delete Save", "fonts/ReemKufi-Regular.ttf", 28);
    auto menuItem = MenuItemLabel::create(labelDelete);
    menuItem ->setCallback([&](cocos2d::Ref *sender) {
        Director::getInstance()->replaceScene(MainMenu::scene());
    });
    auto playButton = MenuItemImage::create("menu/reset-button.png", "menu/reset-button.png",
    	                                        CC_CALLBACK_1(OptionsScene::onDeleteSaveClick, this));
    playButton->setPosition(Vec2(origin.x, origin.y * 2.6));
    playButton->setScale(1.18f);

    // vector of menu items
    Vector<MenuItem *> MenuItems;

    // adding all items
    MenuItems.pushBack(playButton);

    auto menu = Menu::createWithArray(MenuItems);
    	this->addChild(menu, 2);




	//add the menu item for back to main menu
	auto label = Label::createWithTTF("Main Menu", "fonts/ReemKufi-Regular.ttf", 20);
	auto menuItemBack = MenuItemLabel::create(label);
	menuItemBack->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8,
	                           visibleRect.origin.y + onePofScreenH * 5));
	this->addChild(backMenu, 10);


	return true;
}

void OptionsScene::onDeleteSaveClick(cocos2d::Ref *sender) {
	SaveLoad::deleteEverything();
	cocos2d::log("deleteEverything() called");
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.4f, MainMenu::scene(), Color3B(255, 255, 255)));
}
