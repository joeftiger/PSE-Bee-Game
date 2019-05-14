
#ifndef PSE_BEE_GAME_BEEHIVE_H
#define PSE_BEE_GAME_BEEHIVE_H

#include "../Effects/BeeParticles.h"
#include "../Effects/HealthIndicators.h"
#include "cocos2d.h"
#include "../HeaderFiles/Restorable.h"
#include "TileMapLayer.h"
#include "../HeaderFiles/HealthStates.h"

static const int MAX_BEES = 50000;
static const float MAX_RAW_HONEY = 15000;

/**
 * BeeHive object with honey and bees as well as varroa
 */
class BeeHive : Restorable {
private:
	int _beesAlive;
	int _varroaAlive;
	float _rawHoney;
	BeeParticles* _particlesNode;
	HealthIndicators* _healthIndicatorNode;
	cocos2d::Vec2 _position;

	HealthState _currentHealth;

	bool invariant();
	void varroaRandomizer();
	TileMapLayer* _tileMapLayer;

public:
	/**
	 * Creates a new healthy beehive with 4000 bees.
	 */
	explicit BeeHive();

	/**
	 * Creates a new healthy beehive.
	 * @param bees the initial number of bees
	 */
	explicit BeeHive(int bees);

	/**
	 * Creates a new infected beehive
	 * @param bees  the initial number of bees
	 * @param varroa  the initial number of varroa
	 */
	explicit BeeHive(int bees, int varroa);

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
	 * @return number of bees
	 */
	int beesAlive();

	/**
	 * @return number of varroa
	 */
	int varroaAlive();

	/**
	 * @return total raw honey
	 */
	float rawHoney();

	/**
	 * Returns whether the beehive has maxed out its total raw honey.
	 * @return <code>true</code> if raw honey storage is full
	 */
	bool hasFullStorage();

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
     * calculates current health of beehive in relation to varroa
     */
    HealthState currentHealth();

	/**
	 * Removes varroas, but also kills 1000 bees.
	 */
	void killVarroa();

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

	/**
     * Creating the particles for animation
     */
	BeeParticles* getParticles();

	/**
     * returns health indicator
     */
    HealthIndicators* getHealthIndicators();

	void setParticles();

	void setHealthIndicators();

	void setTileMap(TileMapLayer* tileMap);

};

#endif //PSE_BEE_GAME_BEEHIVE_H
