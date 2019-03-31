//
// Created by Uro on 4/1/2019.
//

#include "Container.h"
#include "GameScene.h"
#include "BeeHiveAtlas.h"
#include "HeaderFiles/TileGID.h"
#include "SaveLoad/SaveLoad.h"
#include "ItemPanelLayer.h"
#include "AppDelegate.h"


using namespace cocos2d;

Scene* Container::createScene()
{
    return Container::create();
}

bool Container::init()
{
    if ( !Scene::init()) return false;

    Size visibleSize = Director::getInstance()->getWinSize();

    //Game Scene
    auto gameScene = GameScene::create();
    this->addChild(gameScene);

    //camera
    auto camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    gameScene->addChild(camera, 0, "camera");

    gameScene->setCamera(camera);

    gameScene->setCameraMask((unsigned short) cocos2d::CameraFlag::USER1);

    return true;
}