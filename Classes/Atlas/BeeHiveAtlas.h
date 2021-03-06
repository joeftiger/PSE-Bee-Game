
#ifndef BEEHIVEATLAS_H
#define BEEHIVEATLAS_H

#include "cocos2d.h"
#include "Observer.h"
#include "Game/BeeHive.h"
#include <HeaderFiles/DEFINITIONS.h>
#include "Game/TileMapLayer.h"

/**
 * BeeHiveAtlas that counts, gets, and interacts with BeeHives
 */
class BeeHiveAtlas : public cocos2d::Node, public Observable, public Observer, public Restorable {
private:
	static BeeHiveAtlas *_instance;
	std::map<cocos2d::Vec2, BeeHive *> _beeHives;
	TileMapLayer* _tileMapLayer;

	BeeHiveAtlas() = default;

	BeeHiveAtlas(const BeeHiveAtlas &);

	~BeeHiveAtlas() = default;

public:
	static BeeHiveAtlas *getInstance();

	/**
	 * Stores pointers to beehives in the specified vector.
	 * @param beeHive container for beehive pointers
	 */
	void getBeeHives(std::vector<BeeHive *> &beeHives);

	/**
	 * Returns whether the atlas has a BeeHive obejct at given position.
	 * @param pos position of beehive in tilemap
	 * @return <code>true</code> if associated beehive object. <br><code>false</code> otherwise
	 */
	bool hasBeeHiveAt(const Vec2 &pos);

	/**
	 * Returns the BeeHive object at given position.
	 * @param pos position of beehive in tilemap
	 * @return beehive object
	 */
	BeeHive *getBeeHiveAt(const Vec2 &pos);

	/**
	 * Notifies this BeeHiveAtlas, that the observable has been changed.
	 * The observable should be a TileMapLayer.
	 * @param observable
	 */
	void notify(void *observable) override;

	/**
	 * Updates all beehives in the atlas.
	 */
	void updateBeeHives(float);

	/**
	 * Clears all beehives and resets this beehive atlas to its original state.
	 */
	void clear();

	void toJSON(rapidjson::Document &doc) override;

	void fromJSON(rapidjson::Document &doc) override;
};

#endif //BEEHIVEATLAS_H
