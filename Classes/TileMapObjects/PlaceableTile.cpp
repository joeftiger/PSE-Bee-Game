//
// Created by julius on 14.04.19.
//

#include "PlaceableTile.h"

PlaceableTile *PlaceableTile::createWith(Tiles::TileGID gid) {
    auto node = PlaceableTile::create();
    node->_gid = gid;
    node->addChild(node->getSprite());
    return node;
}

bool PlaceableTile::init() {
    return Placeable::init();
}

bool PlaceableTile::canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
    return tileMapLayer->canPlaceTile(position, _gid);
}

void PlaceableTile::placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) {
    tileMapLayer->placeTile(position, _gid);
}

Sprite *PlaceableTile::getSprite() const {
    return Tiles::getSpriteOf(_gid);
}
