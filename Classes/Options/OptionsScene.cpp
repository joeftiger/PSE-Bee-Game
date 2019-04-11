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
	auto title = Label::createWithTTF("Options", "fonts/OpenSans-ExtraBold.ttf", 48);

	// position the label on the top center of the screen
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(title, 1);

	// Create a title to identify
    auto toggleGraphics= Label::createWithTTF("Use SD Textures? (Not implemented yet)", "fonts/OpenSans-ExtraBold.ttf", 24);

    // position the label above the check box
    toggleGraphics->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + 40+ 0.5*visibleSize.height - title->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(toggleGraphics, 1);

    // checkbox
    auto checkbox = CheckBox::create("menu/CheckBox_Normal.png",
                                     "menu/CheckBox_Press.png",
                                     "menu/CheckBoxNode_Normal.png",
                                     "menu/CheckBox_Disable.png",
                                     "menu/CheckBoxNode_Disable.png");

	checkbox->setScale(1.5f);
    checkbox->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + 0.5*visibleSize.height - title->getContentSize().height));



    checkbox->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                std::cout << "checkbox 1 clicked" << std::endl;
                //TileMapLayer.booleanInverter();
                break;
            default:
                break;
        }
    });

    this->addChild(checkbox, 3);


	//add the menu item for back to main menu
	auto label = Label::createWithTTF("Main Menu", "fonts/OpenSans-Regular.ttf", 20);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8,
	                           visibleRect.origin.y + onePofScreenH * 5));
	this->addChild(backMenu, 10);


	return true;
}
