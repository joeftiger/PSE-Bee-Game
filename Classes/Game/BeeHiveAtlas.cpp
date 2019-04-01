//
// Created by julius on 25.03.19.
//

#include "BeeHiveAtlas.h"
#include "TileMapLayer.h"

BeeHiveAtlas *BeeHiveAtlas::_instance = nullptr;

BeeHiveAtlas *BeeHiveAtlas::getInstance() {
	if (!_instance) {
		_instance = new BeeHiveAtlas;
	}
	return _instance;
}

void BeeHiveAtlas::getBeeHives(std::vector<BeeHive *> *beeHives) {
	beeHives->clear();
	for (auto bh : _beeHives) {
		beeHives->push_back(bh);
	}
}

void BeeHiveAtlas::notify(void *observable) {
	// not a TileMapLayer
	if (typeid(TileMapLayer*) != typeid(observable)) return;

	auto layer = (TileMapLayer *) observable;
	auto positions = layer->getBeeHives();
	bool notifyObservers = false;

	// add missing beehives
	for (const auto &pos : positions) {
		auto index = -1;

		// do we have a hive with that position?
		for (auto i = 0; i < _beeHives.size(); i++) {
			index = i;

			// hive exists
			if (pos == _beeHives[i]->position()) {
				index = -1;
				break;
			}
		}

		// create bee hive
		if (index != -1) {
			auto hive = new BeeHive;
			hive->setPosition(pos);
			_beeHives.push_back(hive);

			notifyObservers = true;
		}
	}

	if (notifyObservers) {
		this->notifyObservers();
	}
}
