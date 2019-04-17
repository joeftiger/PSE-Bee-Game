//
// Created by julius on 14.04.19.
//

#include "PlaceableSprite.h"

bool PlaceableSprite::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	return tileMapLayer->canPlaceSprite(position, 0);
}

void PlaceableSprite::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	tileMapLayer->placeSprite(position, 0);
}
