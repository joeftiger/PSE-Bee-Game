
#include "HoneyExtractor.h"

bool HoneyExtractor::invariant() {
	assert(_honeyInExtractor >= 0);
	return true;
}

HoneyExtractor::HoneyExtractor() : HoneyExtractor(0) {}

//TODO Discuss if this is sufficient?
HoneyExtractor::HoneyExtractor(int _honeyInExtractor) {
	this->_honeyInExtractor = _honeyInExtractor;
	assert(invariant());
	}

bool HoneyExtractor::isEmpty() {
	return _honeyInExtractor <= 0;
}

bool HoneyExtractor::isFull() {
	return _honeyInExtractor >= MAX__HONEY_IN_EXTRACTOR;
}

float HoneyExtractor::honeyInExtractor() {
	return _honeyInExtractor;
}

// TODO Origin of honey from a specific beehive
void HoneyExtractor::addHoneyToExtractor(float amountAdded) {
	if (amountAdded < 0) {
		throw std::out_of_range(
			"[" + std::to_string(amountAdded) + "] is out of range for [_rawHoney = " + std::to_string(_rawHoney) + "]");
	}
	_honeyInExtractor += amountAdded;
	assert(invariant());
}

void HoneyExtractor::update() {
	if (!isEmpty()) {
		Wallet::getInstance()->addMoney(CONVERSION_RATE * MULTIPLIER);
		_honeyInExtractor = fmax (_honeyInExtractor - CONVERSION_RATE, 0.0f);
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
	obj.AddMember("_honeyInExtractor", _honeyInExtractor, doc.GetAllocator());
	obj.AddMember("_posX", int(_position.x), doc.GetAllocator());
	obj.AddMember("_posY", int(_position.y), doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());
}

void HoneyExtractor::fromJSON(rapidjson::Document &doc) {
	assert(doc.HasMember("honeyExtractor"));
	const rapidjson::Value &honeyExtractor = doc["honeyExtractor"];

	assert(honeyExtractor["_honeyInExtractor"].IsFloat());
	_honeyInExtractor = honeyExtractor["_honeyInExtractor"].GetFloat();

	assert(honeyExtractor["_posX"].IsInt());
	_position.x = honeyExtractor["_posX"].GetInt();

	assert(honeyExtractor["_posY"].IsInt());
	_position.y = honeyExtractor["_posY"].GetInt();
}
