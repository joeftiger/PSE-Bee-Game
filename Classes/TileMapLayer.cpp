
#include "TileMapLayer.h"
#include "DEFINITIONS.h"


cocos2d::Layer *TileMapLayer::createLayer() {
    return TileMapLayer::create();
}

bool TileMapLayer::init() {
    if (!Layer::init()) return false;

    _tileMap = TMXTiledMap::create("tilemaps/tilemapHD.tmx");

    this->addChild(_tileMap, -1);
    _tileMap->setAnchorPoint(Point(0.5,0.5));
    _tileMap->setScale(MAP_SCALE);

    return true;
}

ssize_t TileMapLayer::getTreeCount() {
    auto layer = _tileMap->getLayer("trees");
    return layer->getChildren().size();
}

ssize_t TileMapLayer::getFlowerCount() {
    return 3;
}
