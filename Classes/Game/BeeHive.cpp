
#include <cassert>
#include <string>
#include <stdexcept>
#include <Algorithm/GameAlgorithm.h>
#include <Interaction/InteractionNode.h>
#include "BeeHive.h"
#include "GameScene.h"

bool BeeHive::invariant() {
	//assert(_beesAlive >= 0);
	//assert(_varoaAlive >= 0);
	//assert(_rawHoney >= 0.0f);
	return true;
}

BeeHive::BeeHive() : BeeHive(20000) {}

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
	return _beesAlive >= MAX_BEES;
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

void BeeHive::update() {
	if (!isFull()) {
		_beesAlive += GameAlgorithm::getInstance()->nextBees(_beesAlive, _varoaAlive);
	}

	if (!hasFullStorage()) {
		_rawHoney += GameAlgorithm::getInstance()->honeyProduction(_beesAlive);
	}

	if (_varoaAlive >= 0) {
	    _varoaAlive += GameAlgorithm::getInstance()->nextVarroa(_varoaAlive);
	}
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
	obj.AddMember("_varoaAlive", _varoaAlive, doc.GetAllocator());
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

	assert(beeHive["_varoaAlive"].IsInt());
	_varoaAlive = beeHive["_varoaAlive"].GetInt();

	assert(beeHive["_rawHoney"].IsFloat());
	_rawHoney = beeHive["_rawHoney"].GetFloat();

	assert(beeHive["_posX"].IsInt());
	_position.x = beeHive["_posX"].GetInt();

	assert(beeHive["_posY"].IsInt());
	_position.y = beeHive["_posY"].GetInt();
}

bool BeeHive::isInteractable() {
	return _interactable;
}

void BeeHive::doTask() {
    //TODO: add actual implementation
    cocos2d::log("%s", "Interacted with beehive");
    InteractionNode* node = InteractionNode::create();
    node->setFiles("tilemaps/Tiles/bienenstock1_klein.png", "menu/main-menu-background.png");
    GameScene* scene = (GameScene*) Director::getInstance()->getRunningScene();
    scene->getCameraContainer()->addChild(node);
    node->runAnimation();


    std::string s = "raw honey: " + std::to_string(_rawHoney);
    s += "\t bees alive: " + std::to_string(_beesAlive);
    s += "\t varroa alive: " + std::to_string(_varoaAlive);

	// TODO comment in line below once it's running again
    // CCLOG(s.c_str());
}