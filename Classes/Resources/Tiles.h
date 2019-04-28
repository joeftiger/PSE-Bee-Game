#ifndef TILES_H
#define TILES_H

#include "cocos2d.h"

class Tiles {

public:
	enum TileGID {
		beehiveBig = 1,
		beehiveSmall = 2,
		beehiveMiddle = 3,
		flower1 = 11,
		flower2 = 12,
		flower3 = 13,
		flower4 = 14,
		bush1 = 5,
		bush2 = 10,
		bush3 = 15,
		bush4 = 16,
		grass = 17,
		road = 18,
		obstruction = 19,
		no_obstruction = 20
	};

	/**
	 * Returns the sprite corresponding to the given gid.
	 * @param gid gid of tile
	 * @return sprite of tile
	 */
	static cocos2d::Sprite *getSpriteOf(TileGID &gid);
};

#endif /* TILES_H */