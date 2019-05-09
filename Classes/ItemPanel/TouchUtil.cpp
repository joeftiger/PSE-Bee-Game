
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

void TouchUtil::setDrag(const Vec2 &touchPos) {
    for (auto pair : _spritesToPlaceables) {
        if (pair.first->getBoundingBox().containsPoint(touchPos)) {
            _isDrag = true;
            _draggedPlaceable = pair.second;
            _draggedSprite = _draggedPlaceable->getSprite();    // this creates a new sprite -> safe modifications
            _draggedSprite->setPosition(touchPos);
            _draggedSprite->setScale(MAP_SCALE_SD * 1.5f);
            _draggedSprite->setAnchorPoint(Vec2(0.5, 0));
        }
    }
}

Placeable *TouchUtil::getDraggedPlaceable() {
	return _draggedPlaceable;
}

Sprite *TouchUtil::getDraggedSprite() {
	return _draggedSprite;
}

bool TouchUtil::isDrag() {
	return _isDrag;
}

void TouchUtil::addListTo(Layer *layer) {
	for (auto sprite : _spriteList) {
		layer->addChild(sprite);
	}
}

void TouchUtil::addListTo(Scene *scene) {
	for (auto sprite : _spriteList) {
		scene->addChild(sprite);
	}
}

void TouchUtil::setIsDrag(bool isDrag) {
	_isDrag = isDrag;
}
