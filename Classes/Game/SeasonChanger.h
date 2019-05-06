#ifndef SEASONCHANGER_H
#define SEASONCHANGER_H

#include "cocos2d.h"
#include "TileMapLayer.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "Time.h"

using namespace cocos2d;

class SeasonChanger : public Node {

private:

	TileMapLayer * _tileMapLayer;
	Season currentSeason;

public:
	
	static SeasonChanger *create(TileMapLayer *tileMapLayer);

	virtual bool init() override;

	void update(float dt) override;

	void switchToFruehling();
	void switchToSommer();
	void switchToHerbst();
	void switchToWinter();

	//CREATE_FUNC(SeasonChanger);

};

#endif //SEASONCHANGER_H