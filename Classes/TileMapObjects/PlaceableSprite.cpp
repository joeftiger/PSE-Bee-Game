//
// Created by julius on 14.04.19.
//

#include "PlaceableSprite.h"


PlaceableSprite::PlaceableSprite(Sprites::SpriteID id) {
	_id = id;
}

bool PlaceableSprite::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	return tileMapLayer->canPlaceSprite(position, _id);
}

void PlaceableSprite::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	tileMapLayer->placeSprite(position, _id);
}

Sprite *PlaceableSprite::getSprite() {
	return Sprites::getSpriteOf(_id);
}
