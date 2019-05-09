
#include "SeasonChanger.h"

SeasonChanger * SeasonChanger::create(TileMapLayer * tileMapLayer) {
	auto node = SeasonChanger::create();
	node->_tileMapLayer = tileMapLayer;
	node->currentSeason = Time::getInstance()->getSeason();
	return node;
}

bool SeasonChanger::init()
{
	if(!Node::init()) return false;

	this->schedule(schedule_selector(SeasonChanger::update), 0.05f);

	return true;
}


void SeasonChanger::update(float dt) {
	auto nextSeason = Time::getInstance()->getSeason();
	if (nextSeason != currentSeason) {
		switchSeason();
	} 
	if (currentRow >= _tileMapLayer->getLayer()->getLayerSize().height) {
		currentRow = 0;
		currentSeason = nextSeason;
		cocos2d::log("SeasonChanger:\tSwitched to %u", Time::getInstance()->getSeason());
	}
}

void SeasonChanger::switchSeason() {
	
	auto objectLayer = _tileMapLayer->getLayer();

	for (int y = 0; y < objectLayer->getLayerSize().width; y++) {
		int tempGID = objectLayer->getTileGIDAt(Vec2(currentRow, y));
		auto gid = static_cast<Tiles::TileGID>(tempGID);
		objectLayer->setTileGID(Tiles::getSeasonTileGIDof(gid, Time::getInstance()->getSeason()), Vec2(currentRow, y));
	}
	currentRow++;

	/*
	for (int x = 0; x < objectLayer->getLayerSize().height; x++) {
		for (int y = 0; y < objectLayer->getLayerSize().width; y++) {
			int tempGID = objectLayer->getTileGIDAt(Vec2(x, y));
			auto gid = static_cast<Tiles::TileGID>(tempGID);
			objectLayer->setTileGID(Tiles::getSeasonTileGIDof(gid, currentSeason), Vec2(x, y));
		}
	}
	*/
}