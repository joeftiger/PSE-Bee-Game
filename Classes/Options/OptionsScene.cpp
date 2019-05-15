
#include "OptionsScene.h"
#include "../Settings.h"
#include "SaveDeleteConfirmation.h"
#include "MainMenu/MainMenuScene.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;


Scene *OptionsScene::createScene() { return OptionsScene::create(); }

// on "init" you need to initialize your instance
bool OptionsScene::init() {
    // standard size related functions
    cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // adding a background, setting the middle as the anchor point and putting as far back as possible
    auto *backgroundOptions = cocos2d::Sprite::create("menu/main-menu-background-title.png");
    backgroundOptions->setAnchorPoint(Vec2(0.0f, 0.5f));
    backgroundOptions->setPosition(Vec2(0, origin.y));
    this->addChild(backgroundOptions, -1000);

    Vec2 buttonsBed = Vec2(backgroundOptions->getBoundingBox().size.width / 2 + 153.0f,
                           backgroundOptions->getBoundingBox().size.height / 2 - 3.0f);


    // Adding the sprites for the main menu with location and size adjustment
    auto resetButton = ui::Button::create("menu/reset.png");
    resetButton->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->onDeleteSaveClick();
        }
    });
    resetButton->setAnchorPoint(Vec2(0.5f, -0.27f));
    resetButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    resetButton->setScale(1.3f);


    auto textureCheckbox = CheckBox::create("sprites/SD.png", "sprites/HD.png", "sprites/HD.png",
                                            "sprites/SD.png", "sprites/SD.png");
    textureCheckbox->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            Settings::getInstance()->set(Settings::HD_Textures,
                                         !Settings::getInstance()->getAsBool(Settings::HD_Textures));
        }
    });
    textureCheckbox->setSelected(Settings::getInstance()->getAsBool(Settings::Option::HD_Textures));
    textureCheckbox->setAnchorPoint(Vec2(1.025f, 0.5f));
    textureCheckbox->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    textureCheckbox->setScale(1.3f);


    auto showTutorial = CheckBox::create("sprites/tutorial_off.png", "sprites/tutorial_on.png", "sprites/tutorial_on.png",
                                         "sprites/tutorial_off.png", "sprites/tutorial_off.png");
	showTutorial->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Settings::getInstance()->set(Settings::Show_Tutorial,
			                             !Settings::getInstance()->getAsBool(Settings::Show_Tutorial));
		}
	});
	showTutorial->setSelected(Settings::getInstance()->getAsBool(Settings::Option::Show_Tutorial));
    showTutorial->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    showTutorial->setAnchorPoint(Vec2(-0.025f, 0.5f));
    showTutorial->setScale(1.3f);

    auto exitButton = ui::Button::create("menu/exit.png");
    exitButton->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->replaceScene(
                    TransitionFade::create(0.2f, MainMenu::scene(), Color3B(177, 124, 0)));
        }
    });
    exitButton->setAnchorPoint(Vec2(0.5f, 1.27f));
    exitButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    exitButton->setScale(1.3f);

    backgroundOptions->addChild(textureCheckbox);
    backgroundOptions->addChild(resetButton);
    backgroundOptions->addChild(showTutorial);
    backgroundOptions->addChild(exitButton);

    return true;
}

// upon pressing the reset button, delete the save and go back to main menu
void OptionsScene::onDeleteSaveClick() {
    Director::getInstance()->replaceScene(
            TransitionFade::create(0.2f, SaveDeleteConfirmation::createScene(), Color3B(177, 124, 0)));
}
