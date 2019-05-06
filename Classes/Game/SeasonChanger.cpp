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
		switchSeason(currentSeason);
	}
	else if (tempSeason == Season::Summer && currentSeason != Season::Summer) {
		currentSeason = Season::Summer;
		switchSeason(currentSeason);
	}
	else if (tempSeason == Season::Fall && currentSeason != Season::Fall) {
		currentSeason = Season::Fall;
		switchSeason(currentSeason);
	}
	else if (tempSeason == Season::Winter && currentSeason != Season::Winter) {
		currentSeason = Season::Winter;
		switchSeason(currentSeason);
	}
}

void SeasonChanger::switchSeason(Season currentSeason) {
	auto objectLayer = _tileMapLayer->getLayer();

	for (int x = 0; x < objectLayer->getLayerSize().height; x++) {
		for (int y = 0; y < objectLayer->getLayerSize().width; y++) {
			int tempGID = objectLayer->getTileGIDAt(Vec2(x, y));
			auto gid = static_cast<Tiles::TileGID>(tempGID);
			objectLayer->setTileGID(Tiles::getSeasonTileOf(gid, currentSeason), Vec2(x, y));
		}
	}
}