
#include "GameScene.h"
#include "SimpleAudioEngine.h"

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    _tileMap = TMXTiledMap::create("tilemapTobi/mapISO.tmx");
    _background = _tileMap->getLayer("Background");

    this->addChild(_background, -1);
    _background->setAnchorPoint(Point(0.5,0.5));
    _background->setScale(2.0f);

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
    auto position = _background->getPosition();
    _background->setPosition(position + movement);

    this->onTouchBegan(touch, event);
}

void GameScene::onTouchEnded(void *, void *) {
    _isTouched = false;
    _touchPosition = Point(0, 0);
}
