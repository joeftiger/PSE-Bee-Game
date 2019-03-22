
#include "GameScene.h"
#include "DEFINITIONS.h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init()) return false;

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Touch Event Listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Background TileMap
    _tileMapLayer = TileMapLayer::createLayer();
    this->addChild(_tileMapLayer, -1);

    //add the menu item for back to main menu
    auto label = Label::createWithTTF("Main Menu", "fonts/OpenSans-Regular.ttf", 20);
    auto menuItem = MenuItemLabel::create(label);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        Director::getInstance()->replaceScene(MainMenu::scene());
    });

    auto backMenu = Menu::create(menuItem, nullptr);
    backMenu->setPosition(Vec2::ZERO);
    backMenu->setPosition(Vec2(visibleRect.origin.x+visibleRect.size.width - 80, visibleRect.origin.y + 25));
	this->addChild(backMenu, 10);
	
    // HoneyCounter + HoneySprite
    honey = 0;
    honeyLabel = Label::createWithTTF(std::to_string(honey), "fonts/OpenSans-Regular.ttf", TEXT_SIZE_HUD);
    honeyLabel->setPosition(Vec2(visibleRect.origin.x+visibleRect.size.width - 80, visibleRect.origin.y+visibleRect.size.height - 25 ));
    this->addChild(honeyLabel, HUD_PRIORITY);
	auto honeySprite = Sprite::create("sprites/honigglas_2d.png");
	honeySprite->setScale(0.1f);
	honeySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	honeySprite->setPosition(Vec2(40,10));
	honeyLabel->addChild(honeySprite);

	auto beeL = EventListenerTouchOneByOne::create();
	beeL->setSwallowTouches(true);
	beeL->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locInNode = target->convertToNodeSpace(touch->getLocation());
		log("%f %f", locInNode.x, locInNode.y);
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locInNode)) {
			auto s = Sprite::create("sprites/bienenstock.png");
			target->addChild(s, 10);
			s->setPosition(locInNode);
			s->setScale(MAP_SCALE);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(beeL, honeySprite);


	//Timer
	timePassed = 0;
	timeLabel = Label::createWithTTF(std::to_string(timePassed), "fonts/OpenSans-Regular.ttf", TEXT_SIZE_HUD);
	this->addChild(timeLabel, HUD_PRIORITY);
	timeLabel->setPosition(Vec2(visibleRect.origin.x + visibleRect.size.width - 60, visibleRect.origin.y + visibleRect.size.height - 60));
	this->schedule(schedule_selector(GameScene::timer), UPDATE_TIME);
	
    return true;
}

Vec2 GameScene::getclosestTile(Vec2 t)
{
	int x, y;
	for (x = 0; x <= 7; x++) {
		for (y = 0; y <= 7; y++) {
			auto background = _tileMapLayer->getChildByName("background");
		
		}
	}
	return Vec2();
}

void GameScene::timer(float dt) {
	timePassed += dt;
	__String * timeToDisplay = __String::createWithFormat("%.2f", timePassed);
	timeLabel->setString(timeToDisplay->getCString());
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    _isTouched = true;
    _touchPosition = touch->getLocation();
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    auto touchPos = touch->getLocation();
    auto movement = touchPos - _touchPosition;
    auto finalPos = _tileMapLayer->getPosition() + movement;

    _tileMapLayer->setPosition(finalPos);

    this->onTouchBegan(touch, event);
}

void GameScene::onTouchEnded(void *, void *) {
    _isTouched = false;
    _touchPosition = Point(0, 0);
}


