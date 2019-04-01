//
// Created by julius on 25.03.19.
//

#ifndef PSE_BEE_GAME_BEEHIVEATLAS_H
#define PSE_BEE_GAME_BEEHIVEATLAS_H

#include "cocos2d.h"
#include "BeeHive.h"
#include "Observer.h"
#include "TileMapLayer.h"

class BeeHiveAtlas : public Observable, public Observer {
private:
	static BeeHiveAtlas *_instance;
	std::vector<BeeHive*> _beeHives;

public:
	static BeeHiveAtlas *getInstance();

	/**
	 * Stores pointers to beehives in the specified vector.
	 * @param beeHive container for beehive pointers
	 */
	void getBeeHives(std::vector<BeeHive *> *beeHives);

	/**
	 * Notifies this BeeHiveAtlas, that the observable has been changed.
	 * The observable should be a TileMapLayer.
	 * @param observable
	 */
	void notify(void *observable) override;
};

#endif //PSE_BEE_GAME_BEEHIVEATLAS_H
