
#include <Resources/SpriteContainer.h>
#include "Time.h"
#include "SaveLoad/SaveLoad.h"

Time::Time() {
	setStartingMonth();
	_currentSeason = getSeason();
}

void Time::setTileMapLayer(TileMapLayer *tileMapLayer) {
	_tileMapLayer = tileMapLayer;
}

bool Time::invariant() {
	assert(times.seconds >= 0 && times.seconds <= 60);
	assert(times.months >= 0 && times.months < 12);
	assert(times.years >= 0);
	return true;
}

int Time::getMonth() {
	return times.months + 1;
}

void Time::setStartingMonth() {
	cocos2d::log("Time:\tSetting starting month");
	times.months = 2;
}

std::string Time::getMonthAsString() {
	return this->convertToMonth(times.months);
}

std::string Time::convertToMonth(int i)
{
	assert(i >= 0 && i < 12);

	switch (i) {
	case 0: return "Januar";
	case 1: return "Februar";
	case 2: return "Maerz";
	case 3: return "April";
	case 4: return "Mai";
	case 5: return "Juni";
	case 6: return "Juli";
	case 7: return "August";
	case 8: return "September";
	case 9: return "Oktober";
	case 10: return "November";
	case 11: return "Dezember";
	default: return "not possible";
	}
}


Season Time::getSeason() {
	assert(times.months >= 0 && times.months <= 11);
	switch (times.months) {
	
	case 2: 
	case 3:
	case 4: return Season::Spring; //Maerz, April, Mai

	case 5:
	case 6:
	case 7: return Season::Summer; //Juni, Juli, August

	case 8:
	case 9:
	case 10: return Season::Fall; // September, Oktober, November

	case 11:
	case 0:
	case 1: return Season::Winter; // Dezember, Januar, Februar
	default:return Season::Spring;
	}
}

void Time::toJSON(rapidjson::Document & doc) {
	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("timePassed", times.timePassed, doc.GetAllocator());
	obj.AddMember("seconds", times.seconds, doc.GetAllocator());
	obj.AddMember("months", times.months, doc.GetAllocator());
	obj.AddMember("years", times.years, doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());
}

void Time::fromJSON(rapidjson::Document & doc) {
	assert(doc.IsArray());

	const rapidjson::Value &t = doc[0];

	assert(t["timePassed"].IsFloat());
	times.timePassed = t["timePassed"].GetFloat();

	assert(t["seconds"].IsInt());
	times.seconds = t["seconds"].GetInt();

	assert(t["months"].IsInt());
	times.months = t["months"].GetInt();

	assert(t["years"].IsInt());
	times.years = t["years"].GetInt();
}

void Time::update(float dt) {
	times.timePassed += dt;
	if (times.timePassed > 1) {
		times.timePassed -= 1;
		times.seconds++;
	}
	if (times.seconds / 60 >= LENGTH_MONTH) {
		times.seconds = 0;
		times.months++;
	}
	if (times.months >= LENGTH_YEAR) {
		times.months = 0;
		times.years++;
	}

	auto nextSeason = getSeason();
	if (nextSeason != _currentSeason) {
		_currentSeason = nextSeason;
		_currentRow = 0;
		switchSeasonalTrees();
		switchSeasonalTilesSequential();

		cocos2d::log("SeasonChanger:\tSwitched to %i", Time::getInstance()->getSeason());
	} else if (_currentRow < _tileMapLayer->getLayer()->getLayerSize().height) {
		switchSeasonalTilesSequential();
	}
}

void Time::switchSeasonalTrees() {
	for (auto sprite : _tileMapLayer->getSpriteList()) {
		auto seasonID = Sprites::getSeasonSpriteIDof(static_cast<Sprites::SpriteID>(sprite->getTag()), _currentSeason);
		auto frame = SpriteContainer::getInstance()->getSpriteFrameOf(seasonID);
		sprite->setSpriteFrame(frame);
	}
}

void Time::switchSeasonalTilesSequential() {
	auto objectLayer = _tileMapLayer->getLayer();

	for (int y = 0; y < objectLayer->getLayerSize().width; y++) {
		int tempGID = objectLayer->getTileGIDAt(Vec2(_currentRow, y));
		auto gid = static_cast<Tiles::TileGID>(tempGID);
		objectLayer->setTileGID(Tiles::getSeasonTileGIDof(gid, Time::getInstance()->getSeason()), Vec2(_currentRow, y));
	}
	_currentRow++;
}
