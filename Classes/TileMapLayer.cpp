
#include "TileMapLayer.h"
#include "DEFINITIONS.h"
#include "TILE_NAMES.h"

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

std::vector<cocos2d::Sprite*> TileMapLayer::getBeeHives() {
    auto layer = _tileMap->getLayer("objects");
    std::vector<cocos2d::Sprite *> beeHives;

    for (auto y = 0; y < layer->getLayerSize().height; y++) {
        for (auto x = 0; x < layer->getLayerSize().width; x++) {
            auto coordinate = Vec2(x, y);
            cocos2d::Sprite *tile = layer->getTileAt(coordinate);

            if (tile->getName() == BEE_HIVE) {
                beeHives.push_back(tile);
            }
        }
    }
    return beeHives;
}

TMXTiledMap *TileMapLayer::getMap() {
	return _tileMap;
}

void TileMapLayer::subscribe(Observer *observer) {
    // catch re-adding same observer
    for (auto o : _observers) {
        if (o == observer) return;
    }

    _observers.push_back(observer);
}

void TileMapLayer::notifyObservers() {
    for (auto o : _observers) {
        o->notify(this);
    }
}
