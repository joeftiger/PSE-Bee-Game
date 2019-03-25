//
// Created by julius on 22.03.19.
//

#include <cassert>
#include "Player.h"

bool Player::invariant() {
    return true;
}

Player *Player::getInstance() {
    if (!_instance) {
        _instance = new Player();
    }
    return _instance;
}

float Player::TotalRawHoney() {
    float total = 0.0f;
    for (BeeHive bh : _beeHives) {
        total += bh.rawHoney();
    }
    return total;
}
