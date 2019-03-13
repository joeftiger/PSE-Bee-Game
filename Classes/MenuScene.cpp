
#include "MenuScene.h"

Scene* MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init() {

    if ( !Scene::init() )
    {
        return false;
    }

    return true;
}