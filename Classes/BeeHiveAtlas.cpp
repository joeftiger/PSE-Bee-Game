//
// Created by julius on 25.03.19.
//

#include "BeeHiveAtlas.h"
#include "TileMapLayer.h"

BeeHiveAtlas *BeeHiveAtlas::getInstance() {
	if (!_instance) {
		_instance = new BeeHiveAtlas;
		_instance->init();
	}
	return _instance;
}

void BeeHiveAtlas::init() {

}

void BeeHiveAtlas::notify(void *observable) {
	// not a TileMapLayer
	if (typeid(TileMapLayer*) != typeid(observable)) return;

	auto *layer = (TileMapLayer *) observable;
	auto hiveSprites = layer->getBeeHives();

	// remove redundant hives
	for (auto sprite : hiveSprites) {
		int pos = -1;

		// do we already have the hive?
		for (int i = 0; i < _tileHiveLinks.size(); i++) {
			pos = i;
			if (sprite != _tileHiveLinks[i]->beeHiveSprite) {
				pos = -1;
				break;
			}
		}

		if (pos != -1) {
			auto t = _tileHiveLinks[pos];
			_tileHiveLinks.erase(_tileHiveLinks.begin() + pos);
			delete t;   // delete object from memory
		}
	}

	// add missing hives
	for (auto sprite : hiveSprites) {
		bool hasHive = false;

		// do we already have the hive?
		for (auto link : _tileHiveLinks) {
			if (sprite == link->beeHiveSprite) {
				hasHive = true;
				break;
			}
		}

		if (!hasHive) {
			_tileHiveLinks.push_back(new TileHiveLink{sprite, new BeeHive() });
		}
	}
}

void BeeHiveAtlas::getBeeHives(std::vector<BeeHive *> *beeHive) {
	beeHive->clear();
	for (auto link : _tileHiveLinks) {
		beeHive->push_back(link->beeHive);
	}
}
