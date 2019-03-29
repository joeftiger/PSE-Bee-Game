
#include "ShopScene.h"

using namespace cocos2d;

Scene* ShopScene::createScene()
{
    return ShopScene::create();
}

bool ShopScene::init(){
    if ( !Scene::init()) return false;



    return true;
}