
#include <cassert>
#include <string>
#include <stdexcept>
#include <Algorithm/GameAlgorithm.h>
#include <Interaction/InteractionNode.h>
#include "BeeHive.h"
#include "GameScene.h"
#include "../HeaderFiles/HealthStates.h"

bool BeeHive::invariant() {
	//assert(_beesAlive >= 0);
	//assert(_varroaAlive >= 0);
	//assert(_rawHoney >= 0.0f);
	return true;
}

BeeHive::BeeHive() : BeeHive(4000) {}

BeeHive::BeeHive(int bees) : BeeHive(bees, 0) {}

BeeHive::BeeHive(int bees, int varroa) {
	_beesAlive = bees;
	_varroaAlive = varroa;
	_rawHoney = 0;
	_particlesNode = nullptr;
	assert(invariant());
}

bool BeeHive::isEmpty() {
	return _beesAlive <= 0;
}

bool BeeHive::isFull() {
	return _beesAlive >= MAX_BEES;
}

int BeeHive::beesAlive() {
	return _beesAlive;
}

int BeeHive::varroaAlive() {
	return _varroaAlive;
}

float BeeHive::rawHoney() {
	return _rawHoney;
}

bool BeeHive::hasFullStorage() {
	return _rawHoney >= MAX_RAW_HONEY;
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

void BeeHive::killVarroa() {
	_varroaAlive = (int) max(0.0f, _varroaAlive * 0.05f);
    _beesAlive = (int) max(0.0f, _beesAlive * 0.9f);
}

void BeeHive::update() {
	auto alg = GameAlgorithm::getInstance();
	if (!isEmpty()) {
		_beesAlive = (int) clampf(_beesAlive + alg->nextBees(_beesAlive, _varroaAlive), 0, MAX_BEES);
		setParticles();
	}

	if (!hasFullStorage()) {
		_rawHoney = (int) clampf(_rawHoney + alg->honeyProduction(_beesAlive), 0, MAX_RAW_HONEY);
	}

	if (_varroaAlive > 0) {
	    _varroaAlive = (int) clampf(_varroaAlive + alg->nextVarroa(_varroaAlive), 0, std::numeric_limits<int>::max());
	}

	varroaRandomizer();
	assert(invariant());
}

cocos2d::Vec2 BeeHive::position() {
	return _position;
}

void BeeHive::setPosition(const cocos2d::Vec2 &pos) {
	_position.x = pos.x;
	_position.y = pos.y;
}

void BeeHive::toJSON(rapidjson::Document &doc) {
	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("_beesAlive", _beesAlive, doc.GetAllocator());
	obj.AddMember("_varroaAlive", _varroaAlive, doc.GetAllocator());
	obj.AddMember("_rawHoney", _rawHoney, doc.GetAllocator());
	obj.AddMember("_posX", int(_position.x), doc.GetAllocator());
	obj.AddMember("_posY", int(_position.y), doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());
}

void BeeHive::fromJSON(rapidjson::Document &doc) {
	assert(doc.HasMember("beeHive"));
	const rapidjson::Value &beeHive = doc["beeHive"];

	//assert(beeHive.HasMember("_beesAlive"));
	assert(beeHive["_beesAlive"].IsInt());
	_beesAlive = beeHive["_beesAlive"].GetInt();

	assert(beeHive["_varroaAlive"].IsInt());
	_varroaAlive = beeHive["_varroaAlive"].GetInt();

	assert(beeHive["_rawHoney"].IsFloat());
	_rawHoney = beeHive["_rawHoney"].GetFloat();

	assert(beeHive["_posX"].IsInt());
	_position.x = beeHive["_posX"].GetInt();

	assert(beeHive["_posY"].IsInt());
	_position.y = beeHive["_posY"].GetInt();
}

void BeeHive::varroaRandomizer() {
    if(random(0, 10000) < 10) {
        _varroaAlive = (int) random(1, 10);
    }
}

BeeParticles* BeeHive::getParticles() {
    return _particlesNode;
}

void BeeHive::setParticles() {
    _tileMapLayer = (TileMapLayer*) Director::getInstance()->getRunningScene()->getChildByName(TILE_MAP_LAYER_NAME);
    counter++;
    if(!_particlesNode) {
        _particlesNode = BeeParticles::create();
        _tileMapLayer->addChild(_particlesNode);
        _particlesNode->setPosition(Vec2(_tileMapLayer->getLayer()->getTileAt(position())->getPosition() * MAP_SCALE_SD
                                    + _tileMapLayer->getMap()->getTileSize() * MAP_SCALE_SD/2));
    }
    //node movement
    //_particlesNode->setPosition(Vec2(_particlesNode->getPosition().x + random(-1.0, 1.0),
     //       _particlesNode->getPosition().y + random(-1.0, 1.0)));
    _particlesNode->setQuantity(_beesAlive);
}

void BeeHive::setTileMap(TileMapLayer* tileMap) {
    _tileMapLayer = tileMap;
}
