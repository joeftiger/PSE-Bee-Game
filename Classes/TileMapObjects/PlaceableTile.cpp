
#include "PlaceableTile.h"

PlaceableTile::PlaceableTile(Tiles::TileGID gid) {
    _gid = gid;
}

bool PlaceableTile::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
    return tileMapLayer->canPlaceTile(position);
}

void PlaceableTile::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
    tileMapLayer->placeTile(position, _gid);
}

Sprite *PlaceableTile::getSprite() {
    return Tiles::getSpriteOf(_gid);
}
