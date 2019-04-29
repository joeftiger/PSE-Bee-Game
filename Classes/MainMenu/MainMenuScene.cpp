
#include "MainMenuScene.h"

Scene *MainMenu::scene() { return MainMenu::create(); }

// on "init" you need to initialize your instance
bool MainMenu::init() {

	// standard size related functions
	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// adding a background, setting the middle as the anchor point and putting as far back as possible
	auto *background = cocos2d::Sprite::create("menu/main-menu-background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setScale(0.9f);
	this->addChild(background, -1000);

	onePofScreenH = visibleSize.height / 100;
    onePofScreenW = visibleSize.width / 100;

	// Create a title and center it at the top of the screen
	auto title = Label::createWithTTF("So Bee It!", "fonts/ReemKufi-Regular.ttf", 48);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));
	this->addChild(title, 3);

	// Adding the sprites for the main menu with location and size adjustment
	// all scaling and position through trial-and-error
	auto playButton = MenuItemImage::create("menu/start.png", "menu/start.png",
	                                        CC_CALLBACK_1(MainMenu::onPlayClick, this));
	playButton->setPosition(Vec2(origin.x, origin.y * 2.6));
	playButton->setScale(1.04f);

	auto optionsButton = MenuItemImage::create("menu/options.png", "menu/options.png",
	                                           CC_CALLBACK_1(MainMenu::onOptionsClick, this));
	optionsButton->setPosition(Vec2(origin.x - 104, origin.y - 108));
	optionsButton->setScale(1.04f);

	auto aboutButton = MenuItemImage::create("menu/credits.png", "menu/credits.png",
	                                         CC_CALLBACK_1(MainMenu::onAboutClick, this));
	aboutButton->setPosition(Vec2(origin.x + 104, origin.y - 108));
	aboutButton->setScale(1.04f);

	auto exitButton = MenuItemImage::create("menu/exit.png", "menu/exit.png",
    	                                        CC_CALLBACK_1(MainMenu::onExitClick, this));
    exitButton->setPosition(Vec2(origin.x, - origin.y * 4.95));
    exitButton->setScale(1.04f);

	// vector of menu items and then adding all the menu items and creating them
	Vector<MenuItem *> MenuItems;

	MenuItems.pushBack(playButton);
	MenuItems.pushBack(optionsButton);
	MenuItems.pushBack(aboutButton);
	MenuItems.pushBack(exitButton);

	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);


	return true;
}

// when clicking on play - replace scene with game scene
// Delay: 0.6 seconds       Transition Colour: Orange
void MainMenu::onPlayClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.6f, GameScene::create(), Color3B(255, 165, 0)));
}
// when clicking on options - replace scene with options scene
// Delay: 0.4 seconds       Transition Colour: White
void MainMenu::onOptionsClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.4f, OptionsScene::createScene(), Color3B(255, 255, 255)));
}

// when clicking on about - replace scene with about scene
// Delay: 0.4 seconds       Colour: White
void MainMenu::onAboutClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.4f, AboutScene::createScene(), Color3B(255, 255, 255)));
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