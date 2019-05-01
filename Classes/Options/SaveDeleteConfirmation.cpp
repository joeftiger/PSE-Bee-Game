//
// Created by brian on 24/04/2019.
//

#include "SaveDeleteConfirmation.h"
#include "MainMenu/MainMenuScene.h"
#include "OptionsScene.h"
#include "SaveLoad/SaveLoad.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scene *SaveDeleteConfirmation::createScene() { return SaveDeleteConfirmation::create(); }

bool SaveDeleteConfirmation::init() {
	if (!Scene::init()) return false;

	// standard size related functions
	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

	// create a title and set it at the top of the screen
    auto choiceDescription = Label::createWithTTF("Do you wish to carry out the selected action?", "fonts/ReemKufi-Regular.ttf", 48);
    choiceDescription->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - choiceDescription->getContentSize().height));
    this->addChild(choiceDescription, 1);

    // Adding the sprites for the main menu with location and size adjustment
    // all scaling and position through trial-and-error
    auto yesButton = MenuItemImage::create("menu/yes.png", "menu/yes.png",
                                            CC_CALLBACK_1(SaveDeleteConfirmation::onYesClick, this));
    yesButton->setScale(0.5f);
    yesButton->setPosition(Vec2(origin.x - 220, origin.y - 108));


    auto noButton = MenuItemImage::create("menu/no.png", "menu/no.png",
                                                CC_CALLBACK_1(SaveDeleteConfirmation::onNoClick, this));
    noButton->setScale(0.5f);
    noButton->setPosition(Vec2(origin.x + 220, origin.y - 108));


    // vector of menu items and then adding all the menu items and creating them
    Vector<MenuItem*> ConfirmationBoxes;

    ConfirmationBoxes.pushBack(yesButton);
    ConfirmationBoxes.pushBack(noButton);

    auto confirmationChoices = Menu::createWithArray(ConfirmationBoxes);
    this->addChild(confirmationChoices, 2);

	return true;
}

void SaveDeleteConfirmation::onNoClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.1f, OptionsScene::createScene(), Color3B(255, 255, 255)));
}

void SaveDeleteConfirmation::onYesClick(cocos2d::Ref *sender) {
	SaveLoad::deleteEverything();
	cocos2d::log("deleteEverything() called");
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.1f, MainMenu::scene(), Color3B(255, 255, 255)));
}