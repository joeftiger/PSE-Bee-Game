
#include "GameScene.h"
#include "SimpleAudioEngine.h"

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    _tileMap = TMXTiledMap::create("tilemaps/tilemapHD.tmx");
    //_tileMap->set
    _background = _tileMap->getLayer("background");

    this->addChild(_background, -1);
    _background->setAnchorPoint(Point(0.5,0.5));

//    _player = Sprite::create("tilemapTobi/TileGameResources/Player.png");
//    this->addChild(_player);
//
//
//
//    //get spawnpoint
//    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
//    if(objectGroup == NULL) {
//        log("tile map has no objechttps://www.overleaf.com/project/5c66953c90b2c1205f6e5b1et layer");
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
    // is is the same touch as the one for moving the screen?
    if (_isTouched) return false;

    _isTouched = true;
    _touch = touch;
    _touchPosition = _touch->getLocation();
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    // is is the same touch as the one for moving the screen?
    if (_touch != touch) return;

    auto touchPos = touch->getLocation();
    auto movement = touchPos - _touchPosition;
    auto finalPos = _background->getPosition() + movement;

    auto winSize = Director::getInstance()->getVisibleSize();

    float posX, posY;
    _background->getPosition(&posX, &posY);


    _background->setPosition(finalPos);

    this->onTouchBegan(touch, event);
}

void GameScene::onTouchEnded(Touch *touch, void *) {
    // is is the same touch as the one for moving the screen?
    if (_touch != touch) return;

    _isTouched = false;
    _touchPosition = Point(0, 0);
}
