
#include "TileMapLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "HeaderFiles/TILE_NAMES.h"
#include "HeaderFiles/TileGID.h"

bool TileMapLayer::init() {
    if (!Layer::init()) return false;

    _tileMap = TMXTiledMap::create("tilemaps/tilemapHD.tmx");

    this->addChild(_tileMap, -1);
    _tileMap->setAnchorPoint(Point(0,0));
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

Vec2 TileMapLayer::getTilePosition(Vec2 pos) {

	auto box = _tileMap->getBoundingBox();
	auto A = (box.size.width*box.size.height) / 2;
	auto d = sqrt(pow(box.size.width / 2, 2) + pow(box.size.height / 2, 2));
	auto h = A / d;
	auto skew = sqrt(pow(d, 2) - pow(h, 2));
	auto angle = atan(box.size.height / box.size.width);

	pos.x -= box.size.width / 2;
	pos.y -= box.size.height;

	auto temp = pos.x* cos(angle) - pos.y*sin(angle);
	pos.y = pos.x*sin(angle) + pos.y*cos(angle);
	pos.x = temp;

	pos.y *= -1;

	pos.x += skew * (pos.y / h);
	//auto s = std::to_string(pos.x) + "   " + std::to_string(pos.y).c_str();
	pos.x = _tileMap->getMapSize().width*pos.x / d;
	pos.y = _tileMap->getMapSize().height*pos.y / h;

	pos.x = (int)pos.x;
	pos.y = (int)pos.y;
	
	return inTileMapBounds(pos);
}

Vec2 TileMapLayer::inTileMapBounds(Vec2 pos) {
	auto height = _tileMap->getMapSize().height -1;
	auto width = _tileMap->getMapSize().width - 1;
	if (pos.x <= width && pos.y <= height && pos.x >= 0 && pos.y >= 0) {
		return pos;
	}
	else {
		log(height);
		if(pos.x > width && pos.y > height) return Vec2(width, height); //top right
		if(pos.x < 0 && pos.y < 0) return Vec2(0,0); 					//bottom left
		if(pos.x < 0 && pos.y > height) return Vec2(0, height); 		//top left
		if(pos.x > width && pos.y < 0) return Vec2(width, 0);			//bottom right
		if(pos.x < 0) return Vec2(0, pos.y);							//in between y
		if(pos.x > width) return Vec2(width, pos.y);
		if(pos.y < 0) return Vec2(pos.x, 0);							//in between x
		if(pos.y > height) return Vec2(pos.x, height);
		return Vec2(0, 0);
	}
}

void TileMapLayer::setTile(Vec2 position, TileGID gid) {
	auto layer = _tileMap->getLayer("objects");
	layer->setTileGID(gid, getTilePosition(position)); //1 = flower; 2,3,4,5 = bush1,2,3,4; 6 = grass; 7 = road;
}
