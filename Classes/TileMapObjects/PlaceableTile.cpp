//
// Created by julius on 14.04.19.
//

#include "PlaceableTile.h"

PlaceableTile::PlaceableTile(TileGID gid) {
    _gid = gid;
}

bool PlaceableTile::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
    return tileMapLayer->canPlaceTile(position, _gid);
}

void PlaceableTile::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
    tileMapLayer->placeTile(position, _gid);
}
