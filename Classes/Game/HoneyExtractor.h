
#ifndef HONEYEXTRACTOR_H
#define HONEYEXTRACTOR_H

#include "cocos2d.h"
#include "../HeaderFiles/Restorable.h"
#include <cassert>
#include <stdexcept>


static const float MAX__HONEY_IN_EXTRACTOR = 15000;
static const int CONVERSION_RATE = 400;
static const int MULTIPLIER = 1/40;

/**
 * HoneyExtractor object that takes honey and converts it into money.
 */
class HoneyExtractor : Restorable {
private:
	float _honeyInExtractor;
    float _rawHoney;
	cocos2d::Vec2 _position;

	bool invariant();

public:

	/**
	 * Creates a new honey extractor with 0 raw honey as input.
	 */
	explicit HoneyExtractor();

	/**
	 * Creates a new honey extractor with _honeyInExtractor
	 * @param _honeyInExtractor how much honey is in the current extractor
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
	 * @return amount of honey in this extractor
	 */
	float honeyInExtractor();

	/**
	 * adds the specified amount to the extractor
	 * subtracts the specified amount from the total raw honey
	 * @param amountAdded: must be in between <code>[0, rawHoney()]</code>
	 * @throws std::out_of_range() if amount is an invalid value
	 */
	float addHoneyToExtractor(float amountAdded);

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

#endif //HONEYEXTRACTOR_H
