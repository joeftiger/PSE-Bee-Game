
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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto myMenu = Menu::create();

	// Adding the sprites for the main menu TODO: Add "selected" version (second entry)
	auto playButton = MenuItemImage::create("menu/play-button.png","menu/play-button.png",
		CC_CALLBACK_1(MainMenu::onNewGameClick, this));

	auto menu = Menu::create(playButton, NULL);
	this->addChild(menu, 1);

	
	
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
								

    // create menu, it's an autorelease object
    auto closemenu = Menu::create(closeItem, NULL);
    closemenu->setPosition(Vec2::ZERO);
    this->addChild(closemenu, 1);
	
	// Create a Label to identify
	auto label = Label::createWithTTF("Beekeeping Menu", "fonts/OpenSans-Regular.ttf", 24);
	
	// position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
	
	
    /////////////////////////////
    // 3. add main menu
	auto mainmenu = Menu::create();
    int index = 2;
	
	// Label
    auto itemlabel = Label::createWithTTF("Play", "fonts/OpenSans-Regular.ttf", 24);
    auto menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        //TODO Open/Replace the Scene we want 
		//Director::getInstance()->replaceScene(Chapter6_1::createScene());
    });
    menuItem->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2).x,
                          (Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height).y - (++index) * 30));
    
    mainmenu->addChild(menuItem,2);
    mainmenu->setPosition(Vec2::ZERO);
	
	
	
	/* // Menu and Menu Items
    itemlabel = Label::createWithTTF("Options", "fonts/OpenSans-Regular.ttf", 24);
    menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        //TODO Open/Replace the Scene we want
		//Director::getInstance()->replaceScene(Chapter6_2::createScene());
    });
    menuItem->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2).x,
                          (Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height).y - (++index) * 30));
    
    mainmenu->addChild(menuItem,2);
    mainmenu->setPosition(Vec2::ZERO);
	
	// Button
    itemlabel = Label::createWithTTF("Credits", "fonts/OpenSans-Regular.ttf", 24);
    menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
		 //TODO Open/Replace the Scene we want
        //Director::getInstance()->replaceScene(Chapter6_3::createScene());
    });
    menuItem->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2).x,
                          (Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height).y - (++index) * 30));
    
    mainmenu->addChild(menuItem,2);
    mainmenu->setPosition(Vec2::ZERO);


	// add main menu
    mainmenu->setPosition(Vec2::ZERO);
    this->addChild(mainmenu, 1); */
	
    return true;
}

void MainMenu::onNewGameClick(cocos2d::Ref * sender)
{
	//auto gameScene = Scene::create();
	//gameScene->addChild(GamePlay::create());
	//Director::getInstance()->replaceScene(TransitionSlideInT::create(1, gameScene));
	//Without Transistion: 	Director::getInstance()->replaceScene(gameScene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}