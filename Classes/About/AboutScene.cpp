
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

	auto *backgroundAbout = cocos2d::Sprite::create("menu/background.png");
	backgroundAbout->setAnchorPoint(Vec2(0.0f, 0.5f));
    backgroundAbout->setPosition(Vec2(0, origin.y));
    this->addChild(backgroundAbout, -1000);

	onePofScreenH = visibleSize.height / 100;
	onePofScreenW = visibleSize.width / 100;

    Vec2 buttonsBed = Vec2(backgroundAbout->getBoundingBox().size.width / 2 + 153.0f,
                           backgroundAbout->getBoundingBox().size.height / 2 - 3.0f);


	// create a title and set it on the top of the screen
	auto title = Label::createWithTTF("Credits", "fonts/OpenSans-ExtraBold.ttf", 48);
	title->enableOutline(Color4B::BLACK, 1);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
	                        origin.y + visibleSize.height - title->getContentSize().height));
	this->addChild(title, 1);

	// create a richtext button with text about many relevant things
	const auto font = std::string("fonts/OpenSans-Bold.ttf");

    auto text = Label::createWithTTF("Das Spiel wurde erstellt in Zusammenarbeit mit dem Unternehmen Abilium GmbH, von Studenten an der \n"
                         "Universität Bern, als Teil der Vorlesung Praktikum Software Engineering, unter Beratung von Mario Hess.\n\n"
                         "Wir sind:\n"
                         "Mauro Quarta\n"
                         "Alec Schuermann\n"
                         "Julius Oeftiger\n"
                         "Tobias Brugger\n"
                         "Brian Schweigler\n\n"
                         "Artworks von Olivier Fontaine, Logo von Mauro Quarta\n\n"
                         "Mehr Informationen über Bienen sowie Imkern:\n"
                         "Film: 'More Than Honey' (2012) von Markus Imhoof\n"
                         "Eidgenössisches Department für Wirtschaft, Bildung und Forschung: agroscope.admin.ch\n\n"
                         "Danke viel Mals für's Spielen, wir hoffen du hattest Spass!"
                         , font, 28);
	text->enableOutline(Color4B::BLACK, 1);
    text->setAnchorPoint(Vec2(0.61f, -0.03f));
	text->setPosition(Vec2(buttonsBed.x, buttonsBed.y));
	backgroundAbout->addChild(text);


	// add the button for back to main menu on the bottom right corner of the screen
	auto label = Label::createWithTTF("Main Menu", "fonts/ReemKufi-Regular.ttf", 20);
	label->enableOutline(Color4B::BLACK, 1);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MainMenu::scene());
	});
	auto backMenu = Menu::create(menuItem, nullptr);
	backMenu->setPosition(Vec2::ZERO);
	backMenu->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - onePofScreenW * 8.5f,
                                               visibleRect.origin.y + onePofScreenH * 6.0f));
	this->addChild(backMenu, 10);


	return true;
}
