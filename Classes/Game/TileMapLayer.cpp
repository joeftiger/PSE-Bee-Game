#include <Settings.h>
#include "TileMapLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "Resources/Tiles.h"
#include "Resources/Sprites.h"
#include "SaveLoad/SaveLoad.h"
#include "Time.h"
#include <json/stringbuffer.h>
#include <json/writer.h>
#include <TileMapObjects/PlaceableSprite.h>

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

	return true;
}

ssize_t TileMapLayer::getTreeCount() {
	int count = 0;
	for (const auto s : _spriteList) {
		if (Sprites::isTree(static_cast<Sprites::SpriteID>(s->getTag()))) {
			count++;
		}
	}
	return count;
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

std::vector<Sprite *> TileMapLayer::getSpriteList() {
	return _spriteList;
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
			_objectLayer->setTileGID(Tiles::getSeasonTileGIDof(Tiles::grass,
			                                                   Time::getInstance()->getSeason()), tilePos);
		}
	}

	id = Sprites::getSeasonSpriteIDof(id, Time::getInstance()->getSeason());
	auto sprite = Sprites::getSpriteOf(id);
	if (Settings::getInstance()->getAsBool(Settings::HD_Textures)) {
		sprite->setScale(TREE_SCALE_HD);
	} else {
		sprite->setScale(TREE_SCALE_SD);
	}
	sprite->setAnchorPoint(Vec2(0.5f, 0));
	sprite->setPosition(position);
	sprite->setTag(id);

	_spriteList.emplace_back(sprite);
	this->addChild(sprite, pos.x + pos.y);
}

void TileMapLayer::showObstructions(bool visible) {
	_obstructionLayer->setVisible(visible);
}

void TileMapLayer::toJSON(rapidjson::Document & doc) {
	
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);

	writer.StartObject();
	writer.String("TileMap");
	writer.StartArray();
	for (int i = 0; i < _objectLayer->getLayerSize().width; i++) {
		writer.StartArray();
		for (int j = 0; j < _objectLayer->getLayerSize().height; j++) {
			writer.Uint(_objectLayer->getTileGIDAt(Vec2(i, j)));
		}
		writer.EndArray();
	}
	writer.EndArray();

	if (!_spriteList.empty()) {
		writer.String("Sprites");
		writer.StartArray();
		for (auto sprite : _spriteList) {
			writer.StartObject();

			writer.String("id");
			writer.Int(sprite->getTag());

			writer.String("posX");
			writer.Double(sprite->getPositionX());

			writer.String("posY");
			writer.Double(sprite->getPositionY());

			writer.EndObject();
		}
		writer.EndArray();
	}
	writer.EndObject();
	doc.Parse(s.GetString());

}

void TileMapLayer::fromJSON(rapidjson::Document &doc) {
	assert(doc.HasMember("TileMap"));
	rapidjson::Value& tileMap = doc["TileMap"];

	for (rapidjson::SizeType x = 0; x < tileMap.Size(); x++) {

		auto row = tileMap[x].GetArray();

		for (rapidjson::SizeType y = 0; y < row.Size(); y++) {
			assert(row[y].IsInt());
			_objectLayer->setTileGID(row[y].GetInt(), Vec2(x, y));
		}
	}

	if (doc.HasMember("Sprites")) {
		rapidjson::Value& sprites = doc["Sprites"];

		for (rapidjson::SizeType i = 0; i < sprites.Size(); i++) {
			rapidjson::Value& sprite = sprites[i];
			assert(sprite["id"].IsInt());
			assert(sprite["posX"].IsDouble());
			assert(sprite["posY"].IsDouble());

			cocos2d::log("%i", sprite["id"].GetInt());
			cocos2d::log("%f", (float) sprite["posX"].GetDouble());
			cocos2d::log("%f", (float) sprite["posY"].GetDouble());

			auto id = static_cast<Sprites::SpriteID>(sprite["id"].GetInt());
			auto pos = Vec2(sprite["posX"].GetDouble(), sprite["posY"].GetDouble());
			this->place(new PlaceableSprite(id) , pos);
		}
	}
}

void TileMapLayer::loadMap() {
	if (SaveLoad::tileMapSaveExists()) {
		SaveLoad::loadMap(this);
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
