//
// Created by julius on 14.04.19.
//

#include "PlaceableTile.h"

PlaceableTile::PlaceableTile(TileGID gid) {
    _gid = gid;
}

cocos2d::Size PlaceableTile::size() {
    return cocos2d::Size(1, 1);
}

cocos2d::Vec2 PlaceableTile::center() {
    return cocos2d::Vec2(0, 0);
}

bool PlaceableTile::canPlaceOn(TileMapLayer &tileMapLayer, cocos2d::Vec2 &position) {
    return tileMapLayer.canPlaceTile(position, _gid);
}

void PlaceableTile::placeOn(TileMapLayer &tileMapLayer, cocos2d::Vec2 &position) {
    tileMapLayer.placeTile(position, _gid);
}
