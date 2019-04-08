//
// Created by julius on 22.03.19.
//

#include <cassert>
#include "Player.h"
#include "BeeHiveAtlas.h"

Player *Player::_instance = nullptr;

bool Player::invariant() {
	return true;
}

Player *Player::getInstance() {
	if (!_instance) {
		_instance = new Player;
		BeeHiveAtlas::getInstance()->subscribe(*_instance);
	}
	return _instance;
}

float Player::totalRawHoney() {
	float total = 0.0f;
	for (auto bh : _beeHives) {
		total += bh->rawHoney();
	}
	return total;
}

void Player::notify(void *pVoid) {
	BeeHiveAtlas::getInstance()->getBeeHives(_beeHives);
}

std::unordered_map <TileGID, size_t> *Player::getInventory() {
	return _inventory;
}
