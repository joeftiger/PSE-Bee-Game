/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _cam = this->getDefaultCamera();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
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
    _background->setAnchorPoint(Point(0,0));
    _background->setScale(2.0f);

    /*
    //get spawnpoint
    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
    if(objectGroup == NULL) {
        log("tile map has no object layer");
        return false;
    }

    ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
    float xSpawn = spawnPoint["x"].asFloat();
    float ySpawn = spawnPoint["y"].asFloat();
    */

    return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {

    auto touchLocation = touch->getLocation();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);

    Point camPos = _cam->getPosition();
    Point diff = touchLocation - camPos;

    if ( abs(diff.x) > abs(diff.y) ) {
        if (diff.x > 0) {
            camPos.x += _tileMap->getTileSize().width;
        } else {
            camPos.x -= _tileMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            camPos.y -= _tileMap->getTileSize().height;
        } else {
            camPos.y += _tileMap->getTileSize().height;
        }
    }

    // safety check on the bounds of the map
    if (camPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        camPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        camPos.y >= 0 &&
        camPos.x >= 0 )
    {

        this->setCamPosition(camPos);
    }

    //this->setViewPointCenter(_player->getPosition());

}

void HelloWorld::setCamPosition(Point position) {
    _cam->setPosition(position);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
