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
		_instance->schedule(schedule_selector(BeeHiveAtlas::update), 1);
	}
	return _instance;
}

void BeeHiveAtlas::getBeeHives(std::vector <BeeHive> &beeHives) {
	beeHives.clear();
	for (BeeHive &bh : _beeHives) {
		beeHives.emplace_back(bh);
	}
}

void BeeHiveAtlas::notify(void *observable) {
	cocos2d::log("BeeHiveAtlas:\tBeing notified...");

	auto layer = (TileMapLayer *) cocos2d::Director::getInstance()->getRunningScene()->getChildByName(
			TILE_MAP_LAYER_NAME);
	auto positions = layer->getBeeHives();
	bool notifyObservers = false;

	// add missing beehives
	for (const auto &pos : positions) {
		auto hasHive = false;

		// do we have a hive with that position?
		for (auto bh : _beeHives) {
			if (pos == bh.position()) {
				hasHive = true;
				break;
			}
		}

		// FIXME: The BeeHiveAtlas adds beehives even though they already exist.
		// The code looks fine to me though. I am confused.

		// create bee hive
		if (!hasHive) {
			BeeHive hive;
			hive.setPosition(pos);
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
	cocos2d::log("%f", dt);
	for (auto bh : _beeHives) {
		bh.update();
	}
}
