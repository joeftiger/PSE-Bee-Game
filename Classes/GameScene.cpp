
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
    listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //load map
    _tileMap = TMXTiledMap::create("tilemapTobi/mapISO.tmx");
    if(_tileMap == NULL) {
        log("tile map doesnt exist");
        return false;
    }

    //load background
    _background = _tileMap->getLayer("Background");
    if(_background == NULL) {
        log("_background doesnt exist");
        return false;
    }
    this->addChild(_background, -1);
    _background->setAnchorPoint(Point(0.5,0.5));
    _background->setScale(2.0f);

    _player = Sprite::create("tilemapTobi/TileGameResources/Player.png");
    this->addChild(_player);



    //get spawnpoint
    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
    if(objectGroup == NULL) {
        log("tile map has no object layer");
        return false;
    }

    ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
    float xSpawn = spawnPoint["x"].asFloat();
    float ySpawn = spawnPoint["y"].asFloat();

    this->setPlayerPosition(Point(xSpawn,ySpawn));

    auto followPlayer = Follow::create(_player);
    this->runAction(followPlayer);


    return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {

    auto touchLocation = touch->getLocation();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);

    Point playerPos = _player->getPosition();
    Point diff = touchLocation - playerPos;

    if ( abs(diff.x) > abs(diff.y) ) {
        if (diff.x > 0) {
            playerPos.x += _tileMap->getTileSize().width;
        } else {
            playerPos.x -= _tileMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            playerPos.y -= _tileMap->getTileSize().height;
        } else {
            playerPos.y += _tileMap->getTileSize().height;
        }
    }

    /*
    // safety check on the bounds of the map
    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {

        this->setPlayerPosition(playerPos);
    }
    */
    this->setPlayerPosition(playerPos);
}

void GameScene::setPlayerPosition(Point position) {
    _player->setPosition(position);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}
