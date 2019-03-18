

#include "HUDLayer.h"

using namespace cocos2d;


HUDLayer::HUDLayer()
{
}

bool HUDLayer::init() {

    if ( !Layer::init() )
    {
        return false;
    }


    return true;
}

cocos2d::Scene * HUDLayer::scene()
{
	auto scene = Scene::create();
	scene->addChild(HUDLayer::create());
	return scene;
}

