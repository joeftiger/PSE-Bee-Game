//
// Created by julius on 22.03.19.
//

#include <cassert>
#include "Player.h"


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
	float totalRawHoney = 0.0f;
	for (auto bh : _beeHives) {
		totalRawHoney += bh->rawHoney();
	}
	return totalRawHoney;
}

float Player::totalMoney() {
	float totalMoney = 0.0f;
	for (auto he : _honeyExtractors) {
		totalMoney += he->totalMoney();
	}
	return totalMoney;
}

void Player::notify(void *pVoid) {
	BeeHiveAtlas::getInstance()->getBeeHives(_beeHives);
}

std::unordered_map<Placeable, size_t> *Player::getInventory() {
	return _inventory;
}
