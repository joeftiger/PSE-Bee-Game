
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

	auto *background = cocos2d::Sprite::create("menu/menu-background.jpg");
	background->setAnchorPoint(Vec2(0, 0));
	this->addChild(background, -1000); // to ensure it's the lowest layer

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create a title to identify
	auto title = Label::createWithTTF("So Bee It!", "fonts/ReemKufi-Regular.ttf", 48);

	// position the label on the top center of the screen
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(title, 3);


	int index = 2;


	// Adding the sprites for the main menu TODO: Add "selected" version (second entry)
	auto playButton = MenuItemImage::create("menu/start.png", "menu/start.png",
	                                        CC_CALLBACK_1(MainMenu::onPlayClick, this));
	playButton->setPosition(Vec2(origin.x, origin.y).x,
	                        Vec2(origin.x * 2 - visibleSize.width / 8, origin.y * 5 - visibleSize.height / 8).y);
	playButton->setScale(1.5f);
	auto optionsButton = MenuItemImage::create("menu/options.png", "menu/options.png",
	                                           CC_CALLBACK_1(MainMenu::onOptionsClick, this));
	optionsButton->setPosition(Vec2(origin.x - 122, origin.y).x,
	                           Vec2(origin.x * 2 - visibleSize.width / 8 * index,
	                                origin.y  - 112).y);

	optionsButton->setScale(1.5f);
	auto aboutButton = MenuItemImage::create("menu/credits.png", "menu/credits.png",
	                                         CC_CALLBACK_1(MainMenu::onAboutClick, this));
	aboutButton->setPosition(Vec2(origin.x + 122, origin.y).x,
	                         Vec2(origin.x * 2 - visibleSize.width / 8 * index,
	                              origin.y  - 112).y);
	aboutButton->setScale(1.5f);
	// vector of menu items
	Vector < MenuItem * > MenuItems;

	// adding all items
	MenuItems.pushBack(playButton);
	MenuItems.pushBack(optionsButton);
	MenuItems.pushBack(aboutButton);

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
