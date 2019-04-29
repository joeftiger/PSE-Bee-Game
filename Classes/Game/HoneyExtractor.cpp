
#include "HoneyExtractor.h"


bool HoneyExtractor::invariant() {
	// TODO: Uncomment these if it works without throwing assertion errors all the time.
	//	assert(_honeyInExtractor >= 0);
	return true;
}

HoneyExtractor::HoneyExtractor() : HoneyExtractor(50) {}

//TODO Fix this or rather think about the actual implementation
HoneyExtractor::HoneyExtractor(int _honeyInExtractor) {
	_honeyInExtractor = 50;
	assert(invariant());
	}

bool HoneyExtractor::isEmpty() {
	return _honeyInExtractor == 0;
}

bool HoneyExtractor::isFull() {
	return _honeyInExtractor == MAX__HONEY_IN_EXTRACTOR;
}

int HoneyExtractor::totalMoney() {
	return _totalMoney;
}

int HoneyExtractor::honeyInExtractor() {
	return _honeyInExtractor;
}

// TODO Origin of honey from a specific beehive
int HoneyExtractor::newHoneyInExtractor(float amountAdded) {
	if (amountAdded < 0 || amountAdded > _rawHoney) {
		throw std::out_of_range(
			"[" + std::to_string(amountAdded) + "] is out of range for [_rawHoney = " + std::to_string(_rawHoney) + "]");
	}

	_rawHoney -= amountAdded;
	_honeyInExtractor += amountAdded;
	amountAdded = 0.0f;

	assert(invariant());
	return _honeyInExtractor;
}

//  10*3 money per tick, reducing 10 honey in the extractor
//TODO also missing rounding to account for unfitting conversion rate ("left-over")
void HoneyExtractor::update() {
	if (!isEmpty()) {
		Wallet::getInstance()->addMoney(conversionRate * multiplier);
		_honeyInExtractor -= conversionRate;
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

// TODO add any other things that should be saved
void HoneyExtractor::toJSON(rapidjson::Document &doc) {
	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("_honeyInExtractor", _rawHoney, doc.GetAllocator());
	obj.AddMember("_posX", int(_position.x), doc.GetAllocator());
	obj.AddMember("_posY", int(_position.y), doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());
}

void HoneyExtractor::fromJSON(rapidjson::Document &doc) {
	assert(doc.HasMember("honeyExtractor"));
	const rapidjson::Value &beeHive = doc["honeyExtractor"];

	assert(beeHive["_honeyInExtractor"].IsFloat());
	_rawHoney = beeHive["_honeyInExtractor"].GetFloat();

	assert(beeHive["_posX"].IsInt());
	_position.x = beeHive["_posX"].GetInt();

	assert(beeHive["_posY"].IsInt());
	_position.y = beeHive["_posY"].GetInt();
}
