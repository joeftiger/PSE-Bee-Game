
#include <cassert>
#include <string>
#include <stdexcept>
#include "../Algorithm/GameAlgorithm.h"
#include "../Settings.h"
#include "BeeHive.h"
#include "GameScene.h"
#include "../HeaderFiles/HealthStates.h"
#include "Wallet.h"
#include "Story/StoryScene.h"
#include "Game/Prices.h"


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
	_currentHealth = currentHealth();
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
	if (amount < 0) {
		throw std::out_of_range(
				"[" + std::to_string(amount) + "] is out of range for [_rawHoney = " + std::to_string(_rawHoney) + "]");
	}

	amount = min(_rawHoney, amount);
	_rawHoney -= amount;

	assert(invariant());
	return amount;
}

HealthState BeeHive::currentHealth() {
	if (_beesAlive <= 0) {
		//Tutorial
		auto storyScene = StoryScene::getInstance();
		UICustom::Popup* popup = storyScene->createPopup(5);
		if (popup){
			auto scene = (GameScene*) Director::getInstance()->getRunningScene();
			scene->getCameraContainer()->addChild(popup,200);
		}
		return HealthState::Dead;
	}
	if (_varroaAlive <= 20)  return HealthState::Healthy;
	if (_varroaAlive <= 200) return HealthState::Average;
    return HealthState::Unhealthy;
}

void BeeHive::killVarroa() {
    if(Wallet::getInstance()->subtractMoney(Prices::getPriceForMedicine())) {
	    _varroaAlive = (int) max(0.0f, _varroaAlive * 0.05f);
        _beesAlive = (int) max(0.0f, _beesAlive * 0.9f);
    }
}

void BeeHive::update() {
	auto alg = GameAlgorithm::getInstance();
	if(!isDead()) {
	    _beesAlive = (int) clampf(_beesAlive + alg->nextBees(_beesAlive, _varroaAlive, _food, _rawHoney), 0, MAX_BEES);
	    setParticles();
	}

	_rawHoney = (int) clampf(_rawHoney + alg->honeyProduction(_beesAlive, _food), 0, MAX_RAW_HONEY);

	if (_varroaAlive > 0) {
	    _varroaAlive = (int) clampf(_varroaAlive + alg->nextVarroa(_beesAlive, _varroaAlive), 0, std::numeric_limits<int>::max());
	}

    _food = (int) clampf(_food - alg->foodConsumption(_beesAlive), 0, MAX_BEES);

	setHealthIndicators();
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
	obj.AddMember("_food", _food, doc.GetAllocator());
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

	assert(beeHive["_food"].IsInt());
	_food = beeHive["_food"].GetInt();

	assert(beeHive["_posX"].IsInt());
	_position.x = beeHive["_posX"].GetInt();

	assert(beeHive["_posY"].IsInt());
	_position.y = beeHive["_posY"].GetInt();


}

void BeeHive::varroaRandomizer() {
    if(random(0, 10000) < 10 + 10 * (_beesAlive/MAX_BEES)) {
        _varroaAlive = (int) random(1, 10);

        //Tutorial
        auto storyScene = StoryScene::getInstance();
        UICustom::Popup* popup = storyScene->createPopup(2);
        if (popup){
            auto scene = (GameScene*) Director::getInstance()->getRunningScene();
            scene->getCameraContainer()->addChild(popup,200);
        }
    }
}

BeeParticles* BeeHive::getParticles() {
    return _particlesNode;
}

void BeeHive::setParticles() {
    _tileMapLayer = (TileMapLayer*) Director::getInstance()->getRunningScene()->getChildByName(TILE_MAP_LAYER_NAME);
     _mapScale = Settings::getInstance()->getAsFloat(Settings::Map_Scale);

    if(Time::getInstance()->getMonth() > 2 && Time::getInstance()->getMonth() < 10) {
        if(!_particlesNode) {
            _particlesNode = BeeParticles::create();
            _tileMapLayer->addChild(_particlesNode);

            _particlesNode->setPosition(Vec2(_tileMapLayer->getLayer()->getTileAt(position())->getPosition() * _mapScale
                                        + _tileMapLayer->getMap()->getTileSize() * _mapScale / 4));
        } else if(!_particlesNode->isVisible()) {
            _particlesNode->setVisible(true);
        }
        _particlesNode->setQuantity(_beesAlive);
    } else {
        if(_particlesNode) {
            _particlesNode->setVisible(false);
        }
    }
    //node movement
    //_particlesNode->setPosition(Vec2(_particlesNode->getPosition().x + random(-1.0, 1.0),
     //       _particlesNode->getPosition().y + random(-1.0, 1.0)));

}

void BeeHive::setHealthIndicators() {
	if (firstLoad) {
		initHealthBar();
		firstLoad = false;
	}

	if (_currentHealth != currentHealth()) {
		_currentHealth = currentHealth();
		switch (_currentHealth){
			case (Healthy):
				_healthImage->setColor(Color3B::GREEN);
				_healthImage->setPercent(100.0f);
				break;
			case (Average):
				_healthImage->setColor(Color3B::YELLOW);
				_healthImage->setPercent(70.0f);
				break;

			case (Unhealthy):
				_healthImage->setColor(Color3B::RED);
				_healthImage->setPercent(35.0f);
				break;

			case (Dead):
				_healthImage->setColor(Color3B::BLACK);
				_healthImage->setPercent(15.0f);
				break;
			default: // when in doubt, they're healthy
				_healthImage->setColor(Color3B::GREEN);
				_healthImage->setPercent(100.0f);
		}
		
	}
}

void BeeHive::initHealthBar() {
	_tileMapLayer = (TileMapLayer*)Director::getInstance()->getRunningScene()->getChildByName(TILE_MAP_LAYER_NAME);
	_mapScale = Settings::getInstance()->getAsFloat(Settings::Map_Scale);


	// instantiate with "healthy" state image
	_healthImage = ui::LoadingBar::create("indicators/greenSquare_long.png");
	_healthImage->setPercent(100.0f);

	_healthImage->setScale(0.08f);

	_tileMapLayer->addChild(_healthImage, 100);
	auto pos = Vec2(_tileMapLayer->getLayer()->getTileAt(position())->getPosition() * _mapScale
		+ _tileMapLayer->getMap()->getTileSize() * _mapScale / 2);

	// displacement of the indicator
	_healthImage->setPosition(Vec2(pos.x + 10 * _mapScale, pos.y + 10 * _mapScale));

	auto _background = Sprite::create("indicators/progressbar_background.png");
	_healthImage->setAnchorPoint(Vec2(1, -4));
	_healthImage->addChild(_background, 101);
	_background->setPosition(Vec2(_background->getBoundingBox().size.width / 2, _background->getBoundingBox().size.height / 2));
}

void BeeHive::setTileMap(TileMapLayer* tileMap) {
    _tileMapLayer = tileMap;
}


void BeeHive::addFood() {
    if(Wallet::getInstance()->subtractMoney(Prices::getPriceForSugarWater())) {
        _food += 1000;
    }
}

int BeeHive::getFood() {
    return _food;
}

bool BeeHive::isDead() {
	return currentHealth() == HealthState::Dead;
}

void BeeHive::revive() {
	if (Wallet::getInstance()->subtractMoney(300)) {
		this->_beesAlive = 15000;
		this->_varroaAlive = 0;
		this->_food = 0;
		this->_rawHoney = 0;
	}
}