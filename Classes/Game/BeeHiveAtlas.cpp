//
// Created by julius on 25.03.19.
//

#include <HeaderFiles/CHILD_NAMES.h>
#include "BeeHiveAtlas.h"
#include "TileMapLayer.h"
#include <json/stringbuffer.h>
#include <json/writer.h>

BeeHiveAtlas *BeeHiveAtlas::_instance = nullptr;

BeeHiveAtlas *BeeHiveAtlas::getInstance() {
	if (!_instance) {
		cocos2d::log("BeeHiveAtlas:\tCreating instance");
		_instance = new BeeHiveAtlas;
	}

	return _instance;
}

void BeeHiveAtlas::getBeeHives(std::vector<BeeHive *> &beeHives) {
	beeHives.clear();
	for (auto const &pair : _beeHives) {
		beeHives.emplace_back(pair.second);
	}
}

bool BeeHiveAtlas::hasBeeHiveAt(const Vec2 &pos) {
	return _beeHives.count(pos) != 0;
}

BeeHive *BeeHiveAtlas::getBeeHiveAt(const Vec2 &pos) {
	return _beeHives.at(pos);
}

void BeeHiveAtlas::notify(void *observable) {
	bool notifyObservers = false;

	auto layer = (TileMapLayer *) cocos2d::Director::getInstance()->getRunningScene()->getChildByName(
			TILE_MAP_LAYER_NAME);
	if (layer == nullptr) {
		layer = (TileMapLayer *) observable;
		notifyObservers = true;
	}
	auto positions = layer->getBeeHives();

	// add missing beehives
	for (const auto &pos : positions) {
		if (!hasBeeHiveAt(pos)) {
			cocos2d::log("BeeHiveAtlas:\tCreating beehive at (%i, %i)", (int) pos.x, (int) pos.y);
			auto hive = new BeeHive();
			hive->setPosition(pos);
			_beeHives.emplace(pos, hive);

			notifyObservers = true;
		}
	}

	if (notifyObservers) {
		cocos2d::log("BeeHiveAtlas:\tNotifying observers");
		this->notifyObservers();
	}
}

void BeeHiveAtlas::updateBeeHives(float) {
	for (auto const &pair : _beeHives) {
		pair.second->update();
	}
}

void BeeHiveAtlas::clear() {
	_beeHives.clear();
}

void BeeHiveAtlas::toJSON(rapidjson::Document &doc) {
	for (auto const &pair : _beeHives) {
		pair.second->toJSON(doc);
	}
}

void BeeHiveAtlas::fromJSON(rapidjson::Document &doc) {
	_beeHives.clear();

	for (int i = 0; i < doc.Size(); i++) {
		rapidjson::Document subDoc;
		rapidjson::Value &data = doc[i];
		subDoc.SetObject();
		subDoc.AddMember("beeHive", data, subDoc.GetAllocator());

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		subDoc.Accept(writer);
		auto b = new BeeHive();
		b->fromJSON(subDoc);

		_beeHives.emplace(b->position(), b);
	}
}
