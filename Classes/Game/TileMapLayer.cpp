#include <Settings.h>
#include "TileMapLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "Resources/Tiles.h"
#include "Resources/Sprites.h"
#include "SaveLoad/SaveLoad.h"
#include "SeasonChanger.h"

bool TileMapLayer::init() {
	if (!Layer::init()) return false;

	if (Settings::getInstance()->getAsBool(Settings::HD_Textures)) {
		cocos2d::log("TileMaplayer:\tloading HD");
		_tileMap = TMXTiledMap::create("Tilemap/HD/tilemap.tmx");
		_tileMap->setScale(MAP_SCALE_HD);
	} else {
		cocos2d::log("TileMaplayer:\tloading SD");
		_tileMap = TMXTiledMap::create("Tilemap/SD/tilemap.tmx");
		_tileMap->setScale(MAP_SCALE_SD);
	}

	_objectLayer = _tileMap->getLayer("objects");
	_obstructionLayer = _tileMap->getLayer("obstructions");

	this->addChild(_tileMap, -1);
	_tileMap->setAnchorPoint(Point(0, 0));

	this->setName(TILE_MAP_LAYER_NAME);
	this->loadMap();
	this->showObstructions(false);
	
	auto _seasonChanger = SeasonChanger::create(this);
	this->addChild(_seasonChanger);
	_seasonChanger->switchSeason(Time::getInstance()->getSeason());

	return true;
}

ssize_t TileMapLayer::getTreeCount() {
	return 2;
}

ssize_t TileMapLayer::getFlowerCount() {
	auto size = _objectLayer->getLayerSize();
	auto count = 0;

	for (auto y = 0; y < size.height; y++) {
		for (auto x = 0; x < size.width; x++) {
			auto coordinate = Vec2(x, y);
			auto gid = _objectLayer->getTileGIDAt(coordinate);

			if (Tiles::isFlower(static_cast<Tiles::TileGID>(gid))) {
				count++;
			}
		}
	}
	return count;
}

std::vector<cocos2d::Vec2> TileMapLayer::getBeeHives() {
	auto size = _objectLayer->getLayerSize();
	std::vector<cocos2d::Vec2> beeHives;

	for (auto y = 0; y < size.height; y++) {
		for (auto x = 0; x < size.width; x++) {
			auto coordinate = Vec2(x, y);
			auto gid = _objectLayer->getTileGIDAt(coordinate);

			if (Tiles::isBeeHive(static_cast<Tiles::TileGID>(gid))) {
				beeHives.push_back(coordinate);
			}
		}
	}
	return beeHives;
}

std::vector<cocos2d::Vec2> TileMapLayer::getHoneyExtractors() {
	auto size = _objectLayer->getLayerSize();
	std::vector<cocos2d::Vec2> honeyExtractors;

	for (auto y = 0; y < size.height; y++) {
		for (auto x = 0; x < size.width; x++) {
			auto coordinate = Vec2(x, y);
			auto gid = _objectLayer->getTileGIDAt(coordinate);
	//TODO Change this to the honey extractor tile / sprite
			if (gid == Tiles::beehive_big_overflow) {
				honeyExtractors.push_back(coordinate);
			}
		}
	}
	return honeyExtractors;
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

Vec2 TileMapLayer::inTileMapBounds(const Vec2 &pos) {
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

bool TileMapLayer::canPlace(Placeable *placeable, Vec2 &position) {
	return placeable->canPlaceOn(this, position);
}

void TileMapLayer::place(Placeable *placeable, Vec2 &position) {
	assert(canPlace(placeable, position));
	placeable->placeOn(this, position);
}

bool TileMapLayer::canPlaceTile(const Vec2 &position) {
	auto pos = getTilePosition(position);

	return _obstructionLayer->getTileGIDAt(pos) == Tiles::no_obstruction;
}

void TileMapLayer::placeTile(const Vec2 &position, Tiles::TileGID &gid) {
	auto pos = getTilePosition(position);
	_objectLayer->setTileGID(gid, pos);

	if (Tiles::isBeeHive(gid)) {

		_obstructionLayer->setTileGID(Tiles::obstruction, pos);

		notifyObservers();
	}
	// TODO: Implement correct honey extractor gid
	else if (gid == Tiles::beehive_big_overflow) {
		notifyObservers();
	}
}

bool TileMapLayer::canPlaceSprite(const Vec2 &position, const Size &size) {
	auto pos = getTilePosition(position);

	for (auto x = 0; x < size.width; x++) {
		for (auto y = 0; y < size.height; y++) {
			auto tilePos = Vec2(pos.x - x, pos.y - y);

			if (tilePos.x < 0 || tilePos.y < 0) {
				return false;
			}
			if (_obstructionLayer->getTileGIDAt(tilePos) == Tiles::obstruction) {
				return false;
			}
		}
	}
	return true;
}

void TileMapLayer::placeSprite(const Vec2 &position, const Size &size, Sprites::SpriteID id) {
	auto pos = getTilePosition(position);

	for (auto x = 0; x < size.width; x++) {
		for (auto y = 0; y < size.height; y++) {
			auto tilePos = Vec2(pos.x - x, pos.y - y);
			_obstructionLayer->setTileGID(Tiles::obstruction, tilePos);
			_objectLayer->setTileGID(Tiles::getSeasonTileOf(Tiles::grass,
									Time::getInstance()->getSeason()), tilePos);
		}
	}

	auto sprite = Sprites::getSpriteOf(id);
	if (Settings::getInstance()->getAsBool(Settings::HD_Textures)) {
		sprite->setScale(TREE_SCALE_HD);
	} else {
		sprite->setScale(MAP_SCALE_SD);
	}
	sprite->setPosition(position);
	sprite->setAnchorPoint(Vec2(0.5f, 0));
	this->addChild(sprite, pos.x + pos.y);
}

void TileMapLayer::showObstructions(bool visible) {
	_obstructionLayer->setVisible(visible);
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

	if (SaveLoad::honeyExtractorSaveExists()) {
        SaveLoad::loadHoneyExtractors();
    }

	initObstructionLayer();
}

void TileMapLayer::initObstructionLayer() {
	auto size = _objectLayer->getLayerSize();

	for (auto x = 0; x < size.width; x++) {
		for (auto y = 0; y < size.height; y++) {
			auto pos = Vec2(x, y);
			auto gid = _objectLayer->getTileGIDAt(pos);

			if (Tiles::isBeeHive(static_cast<Tiles::TileGID>(gid))) {
				_obstructionLayer->setTileGID(Tiles::obstruction, pos);
			} else {
				_obstructionLayer->setTileGID(Tiles::no_obstruction, pos);
			}
		}
	}
}

