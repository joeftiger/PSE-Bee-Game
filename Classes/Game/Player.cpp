//
// Created by julius on 22.03.19.
//


#include "Player.h"
#include "Wallet.h"
#include "Atlas/BeeHiveAtlas.h"

#include "Atlas/HoneyExtractorAtlas.h"


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

int Player::returnTotalMoney() {
	totalMoney = Wallet::getInstance()->returnTotalMoney();
	return totalMoney;
}

void Player::notify(void *pVoid) {
	BeeHiveAtlas::getInstance()->getBeeHives(_beeHives);
	HoneyExtractorAtlas::getInstance()->getHoneyExtractors(_honeyExtractors);
}

std::unordered_map<Placeable, size_t> *Player::getInventory() {
	return _inventory;
}
