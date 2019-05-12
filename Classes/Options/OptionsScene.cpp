
#include <HeaderFiles/DEFINITIONS.h>
#include "OptionsScene.h"
#include "../Settings.h"
#include "SaveDeleteConfirmation.h"
#include "MainMenu/MainMenuScene.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;


Scene *OptionsScene::createScene() { return OptionsScene::create(); }

// on "init" you need to initialize your instance
bool OptionsScene::init() {
    // standard size related functions
    cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // adding a background, setting the middle as the anchor point and putting as far back as possible
    auto *background = cocos2d::Sprite::create("menu/main-menu-background-title.png");
    background->setAnchorPoint(Vec2(0.0f, 0.5f));
    background->setPosition(Vec2(0, origin.y));
    this->addChild(background, -1000);

    Vec2 buttonsBed = Vec2(background->getBoundingBox().size.width / 2 + 153.0f,
                           background->getBoundingBox().size.height / 2 - 3.0f);


    // Adding the sprites for the main menu with location and size adjustment
    // all scaling and position through trial-and-error
    auto resetButton = ui::Button::create("menu/reset.png");
    resetButton->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            onDeleteSaveClick();
        }
    });
    resetButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    resetButton->setAnchorPoint(Vec2(1.025f, 0.5f));
    resetButton->setAnchorPoint(Vec2(0.5f, -0.27f));
    resetButton->setScale(1.3f);


    auto textureCheckbox = CheckBox::create("Sprites/SD.png", "Sprites/HD.png", "Sprites/HD.png", "Sprites/SD.png",
                                     "Sprites/SD.png");
    textureCheckbox->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            Settings::getInstance()->set(Settings::HD_Textures, !Settings::getInstance()->getAsBool(Settings::HD_Textures));
        }
    });
    textureCheckbox->setSelected(Settings::getInstance()->getAsBool(Settings::SettingName::HD_Textures));
    textureCheckbox->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    textureCheckbox->setAnchorPoint(Vec2(1.025f, 0.5f));
    textureCheckbox->setScale(1.3f);


    auto emptyButton = ui::Button::create("Sprites/empty.png");
    emptyButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    emptyButton->setAnchorPoint(Vec2(-0.025f, 0.5f));
    emptyButton->setScale(1.3f);

    auto exitButton = ui::Button::create("menu/exit.png");
    exitButton->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->replaceScene(MainMenu::scene());
        }
    });
    exitButton->setAnchorPoint(Vec2(0.5f, 1.27f));
    exitButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
    exitButton->setScale(1.3f);

    // Create a title and center it at the top of the screen
    //auto title = Label::createWithTTF("So Bee It!", "fonts/ReemKufi-Regular.ttf", 48);
    //Sprite* title = Sprite::create("menu/title.png");
    //title->setPosition(Vec2(464, buttonsBed.y + 97));
    //background->setScale(visibleSize.height/900);
    //background->addChild(title, 3);

    background->addChild(textureCheckbox);
    background->addChild(resetButton);
    background->addChild(emptyButton);
    background->addChild(exitButton);

    return true;
}

// upon pressing the rest button, delete the save and go back to main menu
void OptionsScene::onDeleteSaveClick() {
    Director::getInstance()->replaceScene(SaveDeleteConfirmation::create());
}
