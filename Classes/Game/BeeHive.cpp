
#include <cassert>
#include <string>
#include <stdexcept>
#include "BeeHive.h"

bool BeeHive::invariant() {
    assert(_beesAlive >= 0);
    assert(_varoaAlive >= 0);
    assert(_rawHoney >= 0.0f);
    return true;
}

BeeHive::BeeHive() : BeeHive(100) {}

BeeHive::BeeHive(int bees) : BeeHive(bees, 0) {}

BeeHive::BeeHive(int bees, int varoa) {
    _beesAlive = bees;
    _varoaAlive = varoa;
    _rawHoney = 0;
    assert(invariant());
}

bool BeeHive::isEmpty() {
    return _beesAlive == 0;
}

bool BeeHive::isFull() {
    return _beesAlive == MAX_BEES;
}

int BeeHive::beesAlive() {
    return _beesAlive;
}

int BeeHive::varoaAlive() {
    return _varoaAlive;
}

float BeeHive::rawHoney() {
    return _rawHoney;
}

bool BeeHive::hasFullStorage() {
    return _rawHoney == MAX_RAW_HONEY;
}

float BeeHive::takeRawHoney() {
    return takeRawHoney(_rawHoney);
}

float BeeHive::takeRawHoney(float amount) {
    if (amount < 0 || amount > _rawHoney) {
        throw std::out_of_range(
                "[" + std::to_string(amount) + "] is out of range for [_rawHoney = " + std::to_string(_rawHoney) + "]");
    }
    _rawHoney -= amount;

    assert(invariant());
    return amount;
}

void BeeHive::update() {
    if (!isFull()) {
        int modifier = std::min(_beesAlive / 100, 20);
        int resultingBees = _beesAlive + modifier;
        _beesAlive = std::min(MAX_BEES, resultingBees);
    }

    if (!hasFullStorage()) {
        float modifier = std::min(_beesAlive / 1000, 5);
        float resultingHoney = _rawHoney + modifier;
        _rawHoney = std::min(MAX_RAW_HONEY, resultingHoney);
    }
    assert(invariant());
}

cocos2d::Vec2 BeeHive::position() {
    return _position;
}

void BeeHive::toJSON(rapidjson::Document &doc) {
    doc.SetObject();
    doc.AddMember("_beesAlive", _beesAlive, doc.GetAllocator());
    doc.AddMember("_varoaAlive", _varoaAlive, doc.GetAllocator());
    doc.AddMember("_rawHoney", _rawHoney, doc.GetAllocator());
    doc.AddMember("_posX", int(_position.x), doc.GetAllocator());
    doc.AddMember("_posY", int(_position.y), doc.GetAllocator());
}

void BeeHive::fromJSON(rapidjson::Document &doc) {
    assert(doc[_beesAlive].IsInt());
    _beesAlive = doc["_beesAlive"].GetInt();

    assert(doc["_varoaAlive"].IsInt());
    _varoaAlive = doc["_varoaAlive"].GetInt();

    assert(doc["_rawHoney"].IsFloat());
    _rawHoney = doc["_rawHoney"].GetFloat();

    assert(doc["_posX"].IsInt());
    _position.x = doc["_posX"].GetInt();

    assert(doc["_posY"].IsInt());
    _position.y = doc["_posY"].GetInt();
}
