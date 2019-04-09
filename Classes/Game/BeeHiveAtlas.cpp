//
// Created by julius on 25.03.19.
//

#include <HeaderFiles/CHILD_NAMES.h>
#include "BeeHiveAtlas.h"
#include "TileMapLayer.h"

BeeHiveAtlas *BeeHiveAtlas::_instance = nullptr;

BeeHiveAtlas *BeeHiveAtlas::getInstance() {
	if (!_instance) {
		_instance = new BeeHiveAtlas;
		Director::getInstance()->getScheduler()->schedule(schedule_selector(BeeHiveAtlas::update), _instance, 1.0f, false);
	}
	
	return _instance;
}

void BeeHiveAtlas::getBeeHives(std::vector <BeeHive *> &beeHives) {
	beeHives.clear();
	for (auto bh : _beeHives) {
		beeHives.emplace_back(bh);
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
		auto hasHive = false;

		// do we have a hive with that position?
		for (auto bh : _beeHives) {
			if (pos == bh->position()) {
				hasHive = true;
				break;
			}
		}

		// create bee hive
		if (!hasHive) {
			auto hive = new BeeHive();
			hive->setPosition(pos);
			_beeHives.emplace_back(hive);

			notifyObservers = true;
		}
	}

	cocos2d::log("BeeHiveAtlas:\tHaving %zu beehives.", _beeHives.size());

	if (notifyObservers) {
		this->notifyObservers();
	}
}

void BeeHiveAtlas::update(float dt) {
	//cocos2d::log("BeeHiveAtlas:\tUpdating beehives.");
	for (auto bh : _beeHives) {
		bh->update();
	}
}

