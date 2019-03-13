

#include "UIScene.h"

Scene* UIScene::createScene() {
    return UIScene::create();
}

bool UIScene::init() {

    if ( !Scene::init() )
    {
        return false;
    }


    return true;
}