//
// Created by Uro on 3/29/2019.
//

#include "TouchUtil.h"
#include <list>
#include <iterator>
#include <iostream>
#include <TileMapObjects/PlaceableTile.h>
#include "HeaderFiles/DEFINITIONS.h"
#include "Resources/Tiles.h"

using namespace cocos2d;
using namespace std;


void TouchUtil::addToPlaceables(Placeable *placeable) {
	_placeables.emplace_back(placeable);
}

void TouchUtil::setDrag(Point screenTouch, Point layerTouch) {
	for (auto sprite : spriteList) {
		if (sprite->getBoundingBox().containsPoint(screenTouch - layerTouch)) {
			auto name = sprite->getResourceName();
			_isDrag = true;
			drag = Sprite::create(name);
			drag->setPosition(screenTouch - layerTouch);
			drag->setTag(sprite->getTag());
			drag->setScale(MAP_SCALE_HD);
			drag->setAnchorPoint(Vec2(0.5f, 0));
		}
	}
}

Sprite *TouchUtil::getDrag() {
	return drag;
}

void TouchUtil::addToSpriteList(string name, Vec2 pos, int tag, Size scale) {
	auto sprite = Sprite::create(name);
	sprite->setTag(tag);
	sprite->setScale(scale.width / (sprite->getBoundingBox().size.width * 3));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(pos.x, pos.y));
	spriteList.push_back(sprite);
}

bool TouchUtil::isDrag() {
	return _isDrag;
}

void TouchUtil::addListTo(Layer *layer) {
	for (auto sprite : spriteList) {
		layer->addChild(sprite);
	}
}

void TouchUtil::addListTo(Scene *scene) {
	for (auto sprite : spriteList) {
		scene->addChild(sprite);
	}
}

void TouchUtil::setIsDrag(bool isDrag) {
	_isDrag = isDrag;
}
