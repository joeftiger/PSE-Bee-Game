#include "SeasonChanger.h"

SeasonChanger * SeasonChanger::create(TileMapLayer * tileMapLayer) {

	SeasonChanger *node = new (std::nothrow) SeasonChanger();
	if (node && node->init()) {
		node->_tileMapLayer = tileMapLayer;

		node->autorelease();
		return node;
	}

	CC_SAFE_DELETE(node);
	return nullptr;
}

bool SeasonChanger::init()
{
	if(!Node::init()) return false;

	this->schedule(schedule_selector(SeasonChanger::update), 1.0f);

	return true;
}


void SeasonChanger::update(float dt) {
	auto tempSeason = Time::getInstance()->getSeason();
	
	if (tempSeason == Season::Spring && currentSeason != Season::Spring) {
		currentSeason = Season::Spring;
		this->switchToFruehling();
	}
	else if (tempSeason == Season::Summer && currentSeason != Season::Summer) {
		currentSeason = Season::Summer;
		this->switchToSommer();
	}
	else if (tempSeason == Season::Fall && currentSeason != Season::Fall) {
		currentSeason = Season::Fall;
		this->switchToHerbst();
	}
	else if (tempSeason == Season::Winter && currentSeason != Season::Winter) {
		currentSeason = Season::Winter;
		this->switchToWinter();
	}
}

void SeasonChanger::switchToFruehling() {
	
	auto objectLayer = _tileMapLayer->getLayer();
	
	for (int x = 0; x < objectLayer->getLayerSize().height - 1; x++) {
		for (int y = 0; y < objectLayer->getLayerSize().width - 1; y++) {
			int tempGID = objectLayer->getTileGIDAt(Vec2(x, y));
			auto gid = static_cast<Tiles::TileGID>(tempGID);
			if (Tiles::isBeeHive(gid)) {
				//objectLayer->setTileGID(11, Vec2(x, y));
			}
		}
	}
	
	log("%s", "Spring");
}

void SeasonChanger::switchToSommer() {
	log("%s", "Summer");
}

void SeasonChanger::switchToHerbst() {
	log("%s", "Fall");
}

void SeasonChanger::switchToWinter() {
	log("%s", "Winter");
}
