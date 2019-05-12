
#include "AboutScene.h"

using namespace cocos2d;

USING_NS_CC;


Scene *AboutScene::createScene() { return AboutScene::create(); }

// on "init" you need to initialize your instance
bool AboutScene::init() {
	if (!Scene::init()) return false;

	// get size related information regarding the screen
	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

	// create a title and set it on the top of the screen
	auto title = Label::createWithTTF("About", "fonts/OpenSans-ExtraBold.ttf", 48);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));
	this->addChild(title, 1);

	// create a richtext button with text about many relevant things
	// TODO Add information, links and maybe images? (18.4)
	auto text = cocos2d::ui::RichText::create();
	const auto font = std::string("fonts/OpenSans-Regular.ttf");
	text->ignoreContentAdaptWithSize(false);
	text->setContentSize(Size(visibleSize.width - 40, visibleSize.height - 40));
	text->pushBackElement(ui::RichElementText::create(0, Color3B::WHITE, 0xff,
	                                                  "Created in cooperation with by Abilium by university of Berne students as part of the Praktikum Software Engineering lecture.",
	                                                  font, 24));
	text->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                       origin.y + visibleSize.height - title->getContentSize().height - 80));
	this->addChild(text, 2);


	// add the button for back to main menu on the bottom right corner of the screen
	auto label = Label::createWithTTF("Main Menu", "fonts/ReemKufi-Regular.ttf", 20);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8,
	                           visibleRect.origin.y + onePofScreenH * 5));
	this->addChild(backMenu, 10);


	return true;
}
