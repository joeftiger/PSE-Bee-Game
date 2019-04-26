//
// Created by brian on 25/04/2019.
//

#ifndef PROJ_ANDROID_HONEYEXTRACTOR_H
#define PROJ_ANDROID_HONEYEXTRACTOR_H


#include "cocos2d.h"
#include "../HeaderFiles/Restorable.h"

static const float MAX__HONEY_IN_EXTRACTOR = 100.0f;

class HoneyExtractor : Restorable {
private:
	int _honeyInExtractor;
	float _rawHoney;
	float _amountAdded;
	int _convertedMoney;
	int modifier;
	float _totalMoney;


	int _money;

	cocos2d::Vec2 _position;

	bool invariant();

public:
	/**
	 * Creates a new honey extractor with 0 raw honey as input.
	 */
	explicit HoneyExtractor();

	/**
     * Creates a new honey extractor with 0 raw honey as input.
     */
    explicit HoneyExtractor(int _honeyInExtractor);

	/**
	 * Returns whether this honey extractor is empty
	 * @return <code>true</code> if no _honeyInExtractor in this hive.
	 */
	bool isEmpty();

	/**
	 * Returns whether this honey extractor is full with honey
	 * @return <code>true</true> if honey extractor is full.
	 */
	bool isFull();

	/**
	 * @return total money
	 */
	float totalMoney();

	/**
	 * TODO write actual Doc for this; do I even need this function?
	 */
	float inputHoneyInExtractor();

	/**
	 * adds the specified amount to the extractor
	 * subtracts the specified amount from the total raw honey
	 * @param amount the amount to take (must be in between <code>[0, rawHoney()]</code>)
	 * @return the amount taken
	 * @throws std::out_of_range() if amount is an invalid value
	 */
	float inputHoneyInExtractor(float amount);

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
