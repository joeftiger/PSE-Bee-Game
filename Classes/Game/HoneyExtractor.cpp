//
// Created by brian on 25/04/2019.
//

#include "HoneyExtractor.h"

#include <cassert>
#include <string>
#include <stdexcept>

bool HoneyExtractor::invariant() {
	assert(_money >= 0); //TODO Variable money
	assert(_rawHoney >= 0.0f);
	return true;
}

HoneyExtractor::HoneyExtractor() : HoneyExtractor(100) {}

HoneyExtractor::HoneyExtractor(int honey) : HoneyExtractor(honey, 0) {}

HoneyExtractor::HoneyExtractor(int honey, int money) {
	_honey = 0;
	assert(invariant());
}

bool HoneyExtractor::isEmpty() {
	return _honey == 0;
}

bool HoneyExtractor::isFull() {
	return _honey == MAX_RAW_HONEY_TO_CONVERT;
}

float HoneyExtractor::rawHoney() {
	return _rawHoney;
}

float HoneyExtractor::takeRawHoney() {
	return takeRawHoney(_rawHoney);
}

float HoneyExtractor::takeRawHoney(float amount) {
	if (amount < 0 || amount > _rawHoney) {
		throw std::out_of_range(
				"[" + std::to_string(amount) + "] is out of range for [_rawHoney = " + std::to_string(_rawHoney) + "]");
	}
	_rawHoney -= amount;

	assert(invariant());
	return amount;
}

void HoneyExtractor::update() {

	if (!isFull()) {
		float modifier = std::min(999 / 100.0f, 100.0f); //TODO input the correct value instead of 999
		float resultingHoney = _rawHoney + modifier;
		_rawHoney = std::min(MAX_RAW_HONEY_TO_CONVERT, resultingHoney);
	}
	assert(invariant());
}

cocos2d::Vec2 HoneyExtractor::position() {
	return _position;
}

void HoneyExtractor::setPosition(const cocos2d::Vec2 &pos) {
	_position.x = pos.x;
	_position.y = pos.y;
}

void HoneyExtractor::toJSON(rapidjson::Document &doc) {
	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("_rawHoney", _rawHoney, doc.GetAllocator());
	obj.AddMember("_posX", int(_position.x), doc.GetAllocator());
	obj.AddMember("_posY", int(_position.y), doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());
}

void HoneyExtractor::fromJSON(rapidjson::Document &doc) {
	assert(doc.HasMember("honeyExtractor"));
	const rapidjson::Value &beeHive = doc["honeyExtractor"];

	assert(beeHive["_rawHoney"].IsFloat());
	_rawHoney = beeHive["_rawHoney"].GetFloat();

	assert(beeHive["_posX"].IsInt());
	_position.x = beeHive["_posX"].GetInt();

	assert(beeHive["_posY"].IsInt());
	_position.y = beeHive["_posY"].GetInt();
}
