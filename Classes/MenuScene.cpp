//Rename this to prevent issues!
// Will be MainMenuScene
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