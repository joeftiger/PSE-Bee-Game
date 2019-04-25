//
// Created by brian on 25/04/2019.
//

#ifndef PROJ_ANDROID_HONEYEXTRACTOR_H
#define PROJ_ANDROID_HONEYEXTRACTOR_H


#include "cocos2d.h"
#include "../HeaderFiles/Restorable.h"

static const float MAX_RAW_HONEY_TO_CONVERT = 2000.0f;

class HoneyExtractor : Restorable {
private:
	float _rawHoney;
	int _honey;
	int _convertedMoney;
	int _money;
	float _rawHoneyToConvert;

	cocos2d::Vec2 _position;

	bool invariant();

public:
	/**
	 * Creates a new healthy beehive with 100 bees.
	 */
	explicit HoneyExtractor();

	/**
	 * Creates a new healthy beehive.
	 * @param bees the initial number of bees
	 */
	explicit HoneyExtractor(int honey);

	/**
	 * Creates a new infected beehive
	 * @param bees  the initial number of bees
	 * @param varoa  the initial number of varoa
	 */
	explicit HoneyExtractor(int honey, int money);

	/**
	 * Returns whether this beehive is empty and has no bees in it.
	 * @return <code>true</code> if no bees in this hive.
	 */
	bool isEmpty();

	/**
	 * Returns whether this beehive has maxed out its bee population.
	 * @return <code>true</true> if beehive is full.
	 */
	bool isFull();

	/**
	 * @return total raw honey
	 */
	float rawHoney();

	/**
	 * Takes and removes the total raw honey currently in the beehive.
	 * @return the total raw honey
	 */
	float takeRawHoney();

	/**
	 * Takes and removes the specified amount from the raw honey currently in the beehive.
	 * @param amount the amount to take (must be in between <code>[0, rawHoney()]</code>)
	 * @return the amount taken
	 * @throws std::out_of_range() if amount is an invalid value
	 */
	float takeRawHoney(float amount);

	/**
	 * @return position in the tilemap
	 */
	cocos2d::Vec2 position();

	/**
	 * Sets the position of the beehive.
	 * @param pos the position
	 */
	void setPosition(const cocos2d::Vec2 &pos);

	/**
	 *
	 */
	void update();

	void toJSON(rapidjson::Document &doc) override;

	void fromJSON(rapidjson::Document &doc) override;
};

#endif //PROJ_ANDROID_HONEYEXTRACTOR_H
