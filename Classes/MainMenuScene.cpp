#include "MainMenuScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene * MainMenu::scene()
{
	cocos2d::Scene * scene = nullptr;
	
	// create a scene
	scene = cocos2d::Scene::create();
	// 'layer' is an autorelease object
    auto * layer = MainMenu::create();
    // add layer as a child to scene
    scene->addChild(layer);
	// return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	// TODO Set our background
	// auto * background = cocos2d::Sprite::create("image/loading.png");

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create a Label to identify
	auto label = Label::createWithTTF("Beekeeping Menu", "fonts/OpenSans-Regular.ttf", 48);
	
	// position the label on the top center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
	
	
    int index = 2;


	// Adding the sprites for the main menu TODO: Add "selected" version (second entry)
	auto playButton = MenuItemImage::create("menu/play-button.png","menu/play-button.png",
		CC_CALLBACK_1(MainMenu::onNewGameClick, this));
	playButton->setPosition(Vec2(origin.x, origin.y).x,
                            Vec2(origin.x*2-visibleSize.width/8, origin.y*2-visibleSize.height/8).y);

	auto optionsButton = MenuItemImage::create("menu/options-button.png","menu/options-button.png",
    		CC_CALLBACK_1(MainMenu::onNewGameClick, this));
    		optionsButton->setPosition(Vec2(origin.x, origin.y).x,
                                        Vec2(origin.x*2-visibleSize.width/8*index, origin.y*2-visibleSize.height/8*index).y);
	++index;
	auto aboutButton = MenuItemImage::create("menu/about-button.png","menu/about-button.png",
    		CC_CALLBACK_1(MainMenu::onNewGameClick, this));
    		aboutButton->setPosition(Vec2(origin.x, origin.y).x,
                                        Vec2(origin.x*2-visibleSize.width/8*index, origin.y*2-visibleSize.height/8*index).y);

	// vector of menu items
	Vector<MenuItem*> MenuItems;

	// adding all items
	MenuItems.pushBack(playButton);
	MenuItems.pushBack(optionsButton);
	MenuItems.pushBack(aboutButton);

	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
								

    // create menu for associated close button, it's an autorelease object
    auto closeMenu = Menu::create(closeItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);
	
	


    return true;
}

void MainMenu::onNewGameClick(cocos2d::Ref * sender)
{
	auto gameScene = Scene::create();
	gameScene->addChild(GameScene::createScene());
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(255,255,255)));
	//Without Transition: 	Director::getInstance()->replaceScene(gameScene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}