#include <HeaderFiles/CHILD_NAMES.h>
#include "TileMapLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "HeaderFiles/TileGID.h"
#include "SaveLoad/SaveLoad.h"

bool TileMapLayer::init() {
    if (!Layer::init()) return false;
	useSD = true;

#if (USE_SD == true)
    cocos2d::log("Using SD");
    _tileMap = TMXTiledMap::create("tilemaps/mapSD.tmx");
    _tileMap->setScale(MAP_SCALE_SD);
#else
    cocos2d::log("Using HD");
    _tileMap = TMXTiledMap::create("tilemaps/tilemapHD.tmx");
    _tileMap->setScale(MAP_SCALE_HD);
#endif

    this->addChild(_tileMap, -1);
    _tileMap->setAnchorPoint(Point(0, 0));

	this->setName(TILE_MAP_LAYER_NAME);
	this->loadMap();
	this->showObstructions(false);
	return true;
}

ssize_t TileMapLayer::getTreeCount() {
	return 2;
}

ssize_t TileMapLayer::getFlowerCount() {
	auto layer = _tileMap->getLayer("objects");
	auto count = 0;

	for (auto y = 0; y < layer->getLayerSize().height; y++) {
		for (auto x = 0; x < layer->getLayerSize().width; x++) {
			auto coordinate = Vec2(x, y);
			auto gid = layer->getTileGIDAt(coordinate);

			if (gid == TileGID::flower1 || gid == TileGID::flower2 || gid == TileGID::flower3 ||
			    gid == TileGID::flower4) {
				count++;
			}
		}
	}
	return count;
}

std::vector <cocos2d::Vec2> TileMapLayer::getBeeHives() {
	auto layer = _tileMap->getLayer("objects");
	std::vector <cocos2d::Vec2> beeHives;

	for (auto y = 0; y < layer->getLayerSize().height; y++) {
		for (auto x = 0; x < layer->getLayerSize().width; x++) {
			auto coordinate = Vec2(x, y);
			auto gid = layer->getTileGIDAt(coordinate);

			if (gid == TileGID::beehiveSmall ||
			    gid == TileGID::beehiveMiddle ||
			    gid == TileGID::beehiveBig) {
				beeHives.push_back(coordinate);
			}
		}
	}
	return beeHives;
}

TMXTiledMap *TileMapLayer::getMap() {
	return _tileMap;
}

TMXLayer *TileMapLayer::getLayer() {
	return _tileMap->getLayer("objects");
}

Vec2 TileMapLayer::getTilePosition(Vec2 pos) {

	auto box = _tileMap->getBoundingBox();
	auto A = (box.size.width * box.size.height) / 2;
	auto d = sqrt(pow(box.size.width / 2, 2) + pow(box.size.height / 2, 2));
	auto h = A / d;
	auto skew = sqrt(pow(d, 2) - pow(h, 2));
	auto angle = atan(box.size.height / box.size.width);

	pos.x -= box.size.width / 2;
	pos.y -= box.size.height;

	auto temp = pos.x * cos(angle) - pos.y * sin(angle);
	pos.y = pos.x * sin(angle) + pos.y * cos(angle);
	pos.x = temp;

	pos.y *= -1;

	pos.x += skew * (pos.y / h);
	//auto s = std::to_string(pos.x) + "   " + std::to_string(pos.y).c_str();
	pos.x = _tileMap->getMapSize().width * pos.x / d;
	pos.y = _tileMap->getMapSize().height * pos.y / h;

	pos.x = (int) pos.x;
	pos.y = (int) pos.y;

	return inTileMapBounds(pos);
}

Vec2 TileMapLayer::inTileMapBounds(const Vec2& pos) {
	auto height = _tileMap->getMapSize().height - 1;
	auto width = _tileMap->getMapSize().width - 1;
	if (pos.x <= width && pos.y <= height && pos.x >= 0 && pos.y >= 0) {
		return pos;
	} else {
		log(height);
		if (pos.x > width && pos.y > height) return Vec2(width, height); //top right
		if (pos.x < 0 && pos.y < 0) return Vec2(0, 0);                    //bottom left
		if (pos.x < 0 && pos.y > height) return Vec2(0, height);        //top left
		if (pos.x > width && pos.y < 0) return Vec2(width, 0);            //bottom right
		if (pos.x < 0) return Vec2(0, pos.y);                            //in between y
		if (pos.x > width) return Vec2(width, pos.y);
		if (pos.y < 0) return Vec2(pos.x, 0);                            //in between x
		if (pos.y > height) return Vec2(pos.x, height);
		return Vec2(0, 0);
	}
}

bool TileMapLayer::canPlaceTile(const Vec2 &position, int gid) {
	auto layer = _tileMap->getLayer("obstructions");
	auto pos = getTilePosition(position);

	return layer->getTileGIDAt(pos) == TileGID::no_obstruction;
}

void TileMapLayer::placeTile(const Vec2 &position, int gid) {
	auto layer = _tileMap->getLayer("objects");
	auto pos = getTilePosition(position);
	layer->setTileGID(gid, pos); //1 = flower; 2,3,4,5 = bush1,2,3,4; 6 = grass; 7 = road

	if (gid == TileGID::beehiveSmall ||
		gid == TileGID::beehiveMiddle ||
		gid == TileGID::beehiveBig) {

		assert(_tileMap->getLayerNum() == 3);
		auto obstructions = _tileMap->getLayer("obstructions");
		assert(obstructions != nullptr);

		obstructions->setTileGID(TileGID::obstruction, pos);

		notifyObservers();
	}
}

void TileMapLayer::showObstructions(bool visible) {
	auto layer = _tileMap->getLayer("obstructions");
	layer->setVisible(visible);
}


void TileMapLayer::loadMap() {
	if (SaveLoad::tileMapSaveExists()) {
		auto data = SaveLoad::loadMap();
		auto layer = this->getLayer();


		for (int x = 0; x < data.size(); x++) {
			for (int y = 0; y < data[x].size(); y++) {
				layer->setTileGID(data[x][y], Vec2(x, y));
			}
		}
	}

	if (SaveLoad::beeHiveSaveExists()) {
		SaveLoad::loadBeehives();
	}

	initObstructionLayer();
}

void TileMapLayer::initObstructionLayer() {
	auto objects = _tileMap->getLayer("objects");
	auto obstructions = _tileMap->getLayer("obstructions");
	auto size = objects->getLayerSize();

	for (auto x = 0; x < size.width; x++) {
		for (auto y = 0; y < size.height; y++) {
			auto pos = Vec2(x, y);
			auto gid = objects->getTileGIDAt(pos);

			if (gid == TileGID::beehiveSmall ||
			    gid == TileGID::beehiveMiddle ||
			    gid == TileGID::beehiveBig) {
				obstructions->setTileGID(TileGID::obstruction, pos);
			} else {
				obstructions->setTileGID(TileGID::no_obstruction, pos);
			}
		}
	}
}

void TileMapLayer::booleanInverter() {
	useSD = !useSD;
}

bool TileMapLayer::canPlace(const Placeable &placeable, const Vec2 &position) {
	return false;
}

void TileMapLayer::place(const Placeable &placeable, const Vec2 &position) {

}

void TileMapLayer::placeTree(const Vec2 &position, int id) {

}
