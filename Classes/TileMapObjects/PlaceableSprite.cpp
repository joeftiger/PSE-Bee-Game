

#include "PlaceableSprite.h"
#include "Game/Prices.h"


PlaceableSprite::PlaceableSprite(Sprites::SpriteID id) {
	_id = id;
	_size = Size(2, 2);
}

const Size &PlaceableSprite::getSize() const {
    return _size;
}

bool PlaceableSprite::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	return tileMapLayer->canPlaceSprite(position, _size);
}

void PlaceableSprite::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
	tileMapLayer->placeSprite(position, _size, _id);
}

Sprite *PlaceableSprite::getSprite() {
	return Sprites::getSpriteOf(_id);
}

int PlaceableSprite::getPrice() {
	return Prices::getPriceForSprite(_id);
}
