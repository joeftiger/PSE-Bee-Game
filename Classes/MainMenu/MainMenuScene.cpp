
#include "MainMenuScene.h"
#include "Game/GameScene.h"
#include "About/AboutScene.h"
#include "Options/OptionsScene.h"
#include "ui/CocosGUI.h"

Scene *MainMenu::scene() { return MainMenu::create(); }

// on "init" you need to initialize your instance
bool MainMenu::init() {

	// standard size related functions
	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Vec2(visibleSize.width/2, visibleSize.height/2);

	// adding a background, setting the middle as the anchor point and putting as far back as possible
	auto *background = cocos2d::Sprite::create("menu/main-menu-background-title.png");
	background->setAnchorPoint(Vec2(0.0f, 0.5f));
	background->setPosition(Vec2(0, origin.y));
	this->addChild(background, -1000);

	Vec2 buttonsBed = Vec2(background->getBoundingBox().size.width/2 + 153.0f,
                           background->getBoundingBox().size.height/2 - 3.0f);


	// Adding the sprites for the main menu with location and size adjustment
    auto playButton = ui::Button::create("menu/start.png");
    playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->onPlayClick();
        }
    });
	playButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
	playButton->setAnchorPoint(Vec2(0.5f, -0.27f));
	playButton->setScale(1.3f);

	auto optionsButton = ui::Button::create("menu/options.png");
    optionsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->onOptionsClick();
        }
    });
	optionsButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
	optionsButton->setAnchorPoint(Vec2(1.025f, 0.5f));
	optionsButton->setScale(1.3f);

    auto aboutButton = ui::Button::create("menu/credits.png");
    aboutButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->onAboutClick();
        }
    });
	aboutButton->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
	aboutButton->setAnchorPoint(Vec2(-0.025f, 0.5f));
	aboutButton->setScale(1.3f);

    auto exitButton = ui::Button::create("menu/exit.png");
    exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->onExitClick();
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

	background->addChild(playButton);
	background->addChild(optionsButton);
	background->addChild(aboutButton);
	background->addChild(exitButton);

	return true;
}

// when clicking on play - replace scene with game scene
// Delay: 0.6 seconds       Transition Colour: Orange
void MainMenu::onPlayClick() {
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::create(), Color3B(177, 124, 0)));
}
// when clicking on options - replace scene with options scene
// Delay: 0.4 seconds       Transition Colour: White
void MainMenu::onOptionsClick() {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.2f, OptionsScene::createScene(), Color3B(177, 124, 0)));
}

// when clicking on about - replace scene with about scene
// Delay: 0.4 seconds       Colour: White
void MainMenu::onAboutClick() {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.2f, AboutScene::createScene(), Color3B(177, 124, 0)));
}

// when clicking on exit - exit the current scene and the game
// no transition or anything similiar to make it as quick as possible
void MainMenu::onExitClick(){
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif

    /*To navigate back to native iOS screen(if present) without quitting the application, do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}