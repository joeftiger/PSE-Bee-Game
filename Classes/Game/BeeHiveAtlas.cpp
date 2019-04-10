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
		_instance = new BeeHiveAtlas;
	}
	
	return _instance;
}

void BeeHiveAtlas::getBeeHives(std::vector <BeeHive *> &beeHives) {
	beeHives.clear();
	for (auto const& pair : _beeHives) {
		beeHives.emplace_back(pair.second);
	}
}

void BeeHiveAtlas::notify(void *observable) {
	cocos2d::log("BeeHiveAtlas:\tBeing notified...");

	auto layer = (TileMapLayer *) cocos2d::Director::getInstance()->getRunningScene()->getChildByName(
			TILE_MAP_LAYER_NAME);
	if (layer == nullptr) {
	    layer = (TileMapLayer *) observable;
	}
	auto positions = layer->getBeeHives();
	bool notifyObservers = false;

	// add missing beehives
	for (const auto &pos : positions) {
		// more efficient direct call than count() > 0
		if (_beeHives.find(pos) == _beeHives.end()) {
			auto hive = new BeeHive();
			hive->setPosition(pos);
			_beeHives.emplace(pos, hive);

			notifyObservers = true;
		}
	}

	cocos2d::log("BeeHiveAtlas:\tHaving %zu beehives.", _beeHives.size());

	if (notifyObservers) {
		this->notifyObservers();
	}
}

void BeeHiveAtlas::updateBeeHives(float dt) {
	for (auto const& pair : _beeHives) {
		pair.second->update();
	}
}

void BeeHiveAtlas::toJSON(rapidjson::Document &doc) {
	for (auto const& pair : _beeHives) {
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
		rapidjson::Writer <rapidjson::StringBuffer> writer(buffer);
		subDoc.Accept(writer);
		auto b = new BeeHive();
		b->fromJSON(subDoc);

		_beeHives.emplace(b->position(), b);
	}
}

