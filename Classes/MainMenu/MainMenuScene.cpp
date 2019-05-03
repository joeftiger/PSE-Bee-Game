
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
	auto *background = cocos2d::Sprite::create("menu/main-menu-background.png");
	background->setAnchorPoint(Vec2(0, 0.5));
	background->setPosition(Vec2(0, origin.y));
	this->addChild(background, -1000);

	Vec2 backgroundOrigin = Vec2(background->getBoundingBox().size.width/2,
                                background->getBoundingBox().size.height/2);

	// Create a title and center it at the top of the screen
	//auto title = Label::createWithTTF("So Bee It!", "fonts/ReemKufi-Regular.ttf", 48);
	Sprite* title = Sprite::create("menu/title.png");
	title->setPosition(Vec2(436, backgroundOrigin.y + 95));
	background->addChild(title, 3);

	// Adding the sprites for the main menu with location and size adjustment
	// all scaling and position through trial-and-error
    auto playButton = ui::Button::create("menu/start.png");

    playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onPlayClick(background);
                break;
        }
    });
	playButton->setPosition(Vec2(backgroundOrigin.x, backgroundOrigin.y));
	playButton->setAnchorPoint(Vec2(0.5, -0.27));
	playButton->setScale(1.3);

	auto optionsButton = ui::Button::create("menu/options.png");
    optionsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onOptionsClick(background);
                break;
        }
    });
	optionsButton->setPosition(Vec2(backgroundOrigin.x, backgroundOrigin.y));
	optionsButton->setAnchorPoint(Vec2(1.025, 0.5));
	optionsButton->setScale(1.3);

    auto aboutButton = ui::Button::create("menu/credits.png");
    aboutButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onAboutClick(background);
                break;
        }
    });
	aboutButton->setPosition(Vec2(backgroundOrigin.x, backgroundOrigin.y));
	aboutButton->setAnchorPoint(Vec2(-0.025, 0.5));
	aboutButton->setScale(1.3);

    auto exitButton = ui::Button::create("menu/exit.png");
    exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onExitClick(background);
                break;
        }
    });
	exitButton->setAnchorPoint(Vec2(0.5, 1.27));
    exitButton->setPosition(Vec2(backgroundOrigin.x, backgroundOrigin.y));
    exitButton->setScale(1.3);

	background->addChild(playButton);
	background->addChild(optionsButton);
	background->addChild(aboutButton);
	background->addChild(exitButton);
	log(to_string(visibleSize.height).c_str());
	background->setScale(visibleSize.height/900);

	return true;
}

// when clicking on play - replace scene with game scene
// Delay: 0.6 seconds       Transition Colour: Orange
void MainMenu::onPlayClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::create(), Color3B(255, 165, 0)));
}
// when clicking on options - replace scene with options scene
// Delay: 0.4 seconds       Transition Colour: White
void MainMenu::onOptionsClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.2f, OptionsScene::createScene(), Color3B(255, 255, 255)));
}

// when clicking on about - replace scene with about scene
// Delay: 0.4 seconds       Colour: White
void MainMenu::onAboutClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.2f, AboutScene::createScene(), Color3B(255, 255, 255)));
}

// when clicking on exit - exit the current scene and the game
// no transition or anything similiar to make it as quick as possible
void MainMenu::onExitClick(cocos2d::Ref *sender){
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}