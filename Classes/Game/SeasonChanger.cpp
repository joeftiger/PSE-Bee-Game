#include "SeasonChanger.h"

SeasonChanger * SeasonChanger::create(TileMapLayer * tileMapLayer) {
	auto node = SeasonChanger::create();
	node->_tileMapLayer = tileMapLayer;
	return node;
}

bool SeasonChanger::init()
{
	if(!Node::init()) return false;

	this->schedule(schedule_selector(SeasonChanger::update), 1.0f);

	return true;
}


void SeasonChanger::update(float dt) {
	auto nextSeason = Time::getInstance()->getSeason();
	if (nextSeason != currentSeason) {
		currentSeason = nextSeason;
		switchSeason();
	}
}

void SeasonChanger::switchSeason() {
	cocos2d::log("SeasonChanger:\tSwitching to %u", currentSeason);
	auto objectLayer = _tileMapLayer->getLayer();

	for (int x = 0; x < objectLayer->getLayerSize().height; x++) {
		for (int y = 0; y < objectLayer->getLayerSize().width; y++) {
			int tempGID = objectLayer->getTileGIDAt(Vec2(x, y));
			auto gid = static_cast<Tiles::TileGID>(tempGID);
			objectLayer->setTileGID(Tiles::getSeasonTileOf(gid, currentSeason), Vec2(x, y));
		}
	}
}