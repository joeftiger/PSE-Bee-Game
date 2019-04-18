
#include "MainMenuScene.h"

cocos2d::Scene *MainMenu::scene() {
	cocos2d::Scene *scene = nullptr;

	// create a scene
	scene = cocos2d::Scene::create();
	// 'layer' is an autorelease object
	auto *layer = MainMenu::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init() {

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto *background = cocos2d::Sprite::create("menu/main-menu-background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setAnchorPoint(Vec2(0.5, 0.5)); // middle of the background sprite
	this->addChild(background, -1000); // to ensure it's the lowest layer


	// Create a title to identify
	auto title = Label::createWithTTF("So Bee It!", "fonts/ReemKufi-Regular.ttf", 48);

	// position the label on the top center of the screen
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(title, 3);


	// Adding the sprites for the main menu with location and size
	auto playButton = MenuItemImage::create("menu/start.png", "menu/start.png",
	                                        CC_CALLBACK_1(MainMenu::onPlayClick, this));
	playButton->setPosition(Vec2(origin.x, origin.y * 2.6));
	playButton->setScale(1.18f);

	auto optionsButton = MenuItemImage::create("menu/options.png", "menu/options.png",
	                                           CC_CALLBACK_1(MainMenu::onOptionsClick, this));
	optionsButton->setPosition(Vec2(origin.x - 104, origin.y - 108));
	optionsButton->setScale(1.18f);

	auto aboutButton = MenuItemImage::create("menu/credits.png", "menu/credits.png",
	                                         CC_CALLBACK_1(MainMenu::onAboutClick, this));
	aboutButton->setPosition(Vec2(origin.x + 104, origin.y - 108));
	aboutButton->setScale(1.18f);

	auto exitButton = MenuItemImage::create("menu/exit.png", "menu/exit.png",
    	                                        CC_CALLBACK_1(MainMenu::onExitClick, this));
    exitButton->setPosition(Vec2(origin.x, - origin.y * 4.95));
    exitButton->setScale(1.18f);

	// vector of menu items
	Vector<MenuItem *> MenuItems;

	// adding all items
	MenuItems.pushBack(playButton);
	MenuItems.pushBack(optionsButton);
	MenuItems.pushBack(aboutButton);
	MenuItems.pushBack(exitButton);

	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 2);

	return true;
}

void MainMenu::onPlayClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(TransitionFade::create(0.6f, GameScene::create(), Color3B(255, 165, 0)));
}

void MainMenu::onOptionsClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.4f, OptionsScene::createScene(), Color3B(255, 255, 255)));
}

void MainMenu::onAboutClick(cocos2d::Ref *sender) {
	Director::getInstance()->replaceScene(
			TransitionFade::create(0.4f, AboutScene::createScene(), Color3B(255, 255, 255)));
}

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