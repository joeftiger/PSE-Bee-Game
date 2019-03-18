
#include "GameScene.h"
#include "SimpleAudioEngine.h"

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

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    _tileMap = TMXTiledMap::create("tilemaps/tilemapHD.tmx");
    _background = _tileMap->getLayer("background");

    this->addChild(_tileMap, -1);
    _tileMap->setAnchorPoint(Point(0.5,0.5));


    //add the menu item for back to main menu
    auto label = Label::createWithTTF("Main Menu", "fonts/OpenSans-Regular.ttf", 18);
    auto menuItem = MenuItemLabel::create(label);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        Director::getInstance()->replaceScene(MainMenu::scene());
    });

    auto backMenu = Menu::create(menuItem, nullptr);
    backMenu->setPosition(Vec2::ZERO);
    backMenu->setPosition(Vec2(visibleRect.origin.x+visibleRect.size.width - 80, visibleRect.origin.y + 25));
	this->addChild(backMenu, 1);

//    _player = Sprite::create("tilemapTobi/TileGameResources/Player.png");
//    this->addChild(_player);
//
//
//
//    //get spawnpoint
//    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
//    if(objectGroup == NULL) {
//        log("tile map has no object layer");
//        return false;
//    }
//
//    ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
//    float xSpawn = spawnPoint["x"].asFloat();
//    float ySpawn = spawnPoint["y"].asFloat();
//
//    this->setPlayerPosition(Point(xSpawn,ySpawn));
//
//    auto followPlayer = Follow::create(_player);
//    this->runAction(followPlayer);


    // Honeycounter
    int honey = 0;
    auto honeyLabel = Label::createWithTTF(std::to_string(honey), "fonts/OpenSans-Regular.ttf", 20);
    honeyLabel->setPosition(Vec2(visibleRect.origin.x+visibleRect.size.width - 80, visibleRect.origin.y+visibleRect.size.height - 25 ));
    this->addChild(honeyLabel,1);



    return true;
}

void GameScene::setPlayerPosition(Point position) {
    _player->setPosition(position);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    _isTouched = true;
    _touchPosition = touch->getLocation();
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    auto touchPos = touch->getLocation();
    auto movement = touchPos - _touchPosition;
    auto finalPos = _background->getPosition() + movement;

    auto winSize = Director::getInstance()->getVisibleSize();

    float posX, posY;
    _background->getPosition(&posX, &posY);


    _background->setPosition(finalPos);

    this->onTouchBegan(touch, event);
}

void GameScene::onTouchEnded(void *, void *) {
    _isTouched = false;
    _touchPosition = Point(0, 0);
}
