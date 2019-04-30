//
// Created by julius on 14.04.19.
//

#include "PlaceableSprite.h"

PlaceableSprite *PlaceableSprite::createWith(Sprites::SpriteID id) {
	auto node = PlaceableSprite::create();
	node->_id = id;
	node->_size = Size(2, 2);
	return nullptr;
}

bool PlaceableSprite::init() {
	return Placeable::init();
}

const Size &PlaceableSprite::getSize() const {
    return _size;
}

bool PlaceableSprite::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	return tileMapLayer->canPlaceSprite(position, _size, _id);
}

void PlaceableSprite::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	tileMapLayer->placeSprite(position, _size, _id);
}

Sprite *PlaceableSprite::getSprite() const {
	return Sprites::getSpriteOf(_id);
}
