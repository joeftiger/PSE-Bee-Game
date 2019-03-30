//
// Created by Uro on 3/29/2019.
//

#include "TouchUtil.h"
#include <list>
#include <iterator>
#include <iostream>
#include "HeaderFiles/DEFINITIONS.h"
#include "HeaderFiles/TILE_NAMES.h"
#include "HeaderFiles/TileGID.h"

using namespace cocos2d;
using namespace std;


Sprite *TouchUtil::getDrag(Point screenTouch, Point layerTouch) {
    for(auto sprite : spriteList)
    {
        if (sprite->getBoundingBox().containsPoint(screenTouch - layerTouch)) {
            auto name = sprite->getResourceName();
            _isDrag = true;
            drag = Sprite::create(name);
            drag->setPosition(screenTouch);
            drag->setTag(sprite->getTag());
            drag->setScale(MAP_SCALE / 2);
            drag->setAnchorPoint(Vec2(0.5f, 0));
            return drag;
        }
    }
}

void TouchUtil::addToSpriteList(string name, Vec2 pos, int tag) {
    auto sprite = Sprite::create(name);
    sprite->setTag(tag);
    sprite->setScale(0.2f);
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(Vec2(pos.x, pos.y));
    spriteList.push_back(sprite);
}

bool TouchUtil::isDrag() {
    return _isDrag;
}

void TouchUtil::addListTo(Layer *layer) {
    for(auto sprite : spriteList) {
        layer->addChild(sprite);
    }
}
void TouchUtil::addListTo(Scene *scene) {
    for(auto sprite : spriteList) {
        scene->addChild(sprite);
    }
}


