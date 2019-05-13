#ifndef TIME_H
#define TIME_H

#include "cocos2d.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "HeaderFiles/Restorable.h"
#include "HeaderFiles/TimeStruct.h"
#include "json/rapidjson.h"
#include "HeaderFiles/Seasons.h"
#include "TileMapLayer.h"

using namespace cocos2d;

/**
 *	for dealing with, getting a month, setting the starting month and interacting with seasons aswell as change seasons
 */
class Time: public Restorable  {
private:
	timeStruct times;

	int _currentRow = 0;
	TileMapLayer * _tileMapLayer;
	Season _currentSeason;

	//Time() = default;

	Time(const Time &);

	//~Time() final = default;

	/**
     *	Convert int to months
     */
	std::string convertToMonth(int i);

public:

	Time();

	void setTileMapLayer(TileMapLayer *tileMapLayer);

	static Time *getInstance() {
		static auto instance = new Time();
		return instance;
	}

	void update(float dt);

	bool invariant();

	void clear();

	int getMonth();

	void setStartingMonth();

	std::string getMonthAsString();

	Season getSeason();

	/**
	 * Switches the tilemap's trees to the current season.
	 */
	void switchSeasonalTrees();

	/**
	 * Switches the tilemap's tiles sequentially (row by row) to the current season.
	 */
	void switchSeasonalTilesSequential();

	void toJSON(rapidjson::Document &doc) override;

	void fromJSON(rapidjson::Document &doc) override;

};

#endif //TIME_H
