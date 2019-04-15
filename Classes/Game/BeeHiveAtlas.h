//
// Created by julius on 25.03.19.
//

#ifndef PSE_BEE_GAME_BEEHIVEATLAS_H
#define PSE_BEE_GAME_BEEHIVEATLAS_H

#include "cocos2d.h"
#include "BeeHive.h"
#include "Observer.h"
#include "TileMapLayer.h"

class BeeHiveAtlas : public cocos2d::Node, public Observable, public Observer, public Restorable {
private:
	static BeeHiveAtlas *_instance;
	std::map <cocos2d::Vec2, BeeHive *> _beeHives;

	BeeHiveAtlas() = default;

	BeeHiveAtlas(const BeeHiveAtlas &);

	~BeeHiveAtlas() = default;

public:
	static BeeHiveAtlas *getInstance();

	/**
	 * Stores pointers to beehives in the specified vector.
	 * @param beeHive container for beehive pointers
	 */
	void getBeeHives(std::vector <BeeHive *> &beeHives);

	/**
	 * Returns the BeeHive object at given position.
	 * @param pos position of beehive in tilemap
	 * @return beehive object
	 */
	BeeHive *getBeeHiveAt(const Vec2& pos);

	/**
	 * Notifies this BeeHiveAtlas, that the observable has been changed.
	 * The observable should be a TileMapLayer.
	 * @param observable
	 */
	void notify(void *observable) override;

	void updateBeeHives(float dt);

	void toJSON(rapidjson::Document &doc) override;

	void fromJSON(rapidjson::Document &doc) override;
};

#endif //PSE_BEE_GAME_BEEHIVEATLAS_H
