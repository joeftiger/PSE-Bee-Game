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
	
	if (tempSeason == Season::Fruehling && currentSeason != Season::Fruehling) {
		currentSeason = Season::Fruehling;
		this->switchToFruehling();
	}
	else if (tempSeason == Season::Sommer && currentSeason != Season::Sommer) {
		currentSeason = Season::Sommer;
		this->switchToSommer();
	}
	else if (tempSeason == Season::Herbst && currentSeason != Season::Herbst) {
		currentSeason = Season::Herbst;
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
	
	log("%s", "Fruehling");
}

void SeasonChanger::switchToSommer() {
	log("%s", "Sommer");
}

void SeasonChanger::switchToHerbst() {
	log("%s", "Herbst");
}

void SeasonChanger::switchToWinter() {
	log("%s", "Winter");
}
