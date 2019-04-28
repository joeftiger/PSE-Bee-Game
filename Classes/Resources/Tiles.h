#ifndef TILES_H
#define TILES_H

#include "cocos2d.h"

class Tiles {
private:
	static std::map<int, cocos2d::Sprite *> _tileSprites;

	static void addSprites();

public:
	enum TileGID {
		beehiveBig1 = 1,
		beehiveSmall1 = 2,
		beehiveMiddle1 = 3,
		// open beehiveBig1
		beehiveBig2 = 4,
		// open beehiveSmall1
		beehiveSmall2 = 6,
		// open beehiveMiddle1
		beehiveMiddle2 = 7,
		// overflowing beehiveBig1
		beehiveBig3 = 8,
		// overflowing beehiveMiddle1
		beehiveMiddle3 = 9,
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