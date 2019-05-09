#ifndef TILES_H
#define TILES_H

#include <HeaderFiles/Seasons.h>
#include "cocos2d.h"

class Tiles {
public:
    enum TileGID : unsigned int {
	    beehive_small           = 1,
	    beehive_middle          = 2,
	    beehive_big             = 3,
	    beehive_small_open      = 4,
	    beehive_middle_open     = 5,
        beehive_big_open        = 6,
        beehive_middle_overflow = 7,
	    beehive_big_overflow    = 8,
	    grass                   = 9,
	    road                    = 10,
	    beehive_small_winter    = 11,
	    beehive_middle_winter   = 12,
	    beehive_big_winter      = 13,
	    flower_blue_small       = 14,
	    flower_blue_middle      = 15,
	    flower_blue_big         = 16,
	    flower_red_small        = 17,
	    flower_red_middle       = 18,
	    flower_red_big          = 19,
	    snow                    = 20,
	    brushwood_small         = 21,
	    bush_small              = 22,
	    bush_big                = 23,
	    brushwood_big           = 24,
	    flower_white_small      = 25,
	    flower_white_middle     = 26,
	    flower_white_big        = 27,
	    flower_pink_small       = 28,
	    flower_pink_middle      = 29,
	    flower_pink_big         = 30,
	    brushwood_small_winter  = 31,
	    bush_small_winter       = 32,
	    bush_big_winter         = 33,
	    brushwood_big_winter    = 34,
	    snow_1                  = 35,
	    snow_2                  = 36,
	    snow_3                  = 37,
	    snow_4                  = 38,
	    no_obstruction          = 39,
	    obstruction             = 40
    };

    /**
     * Returns whether the given tile gid is of type beehive.
     * @param gid tile gid
     * @return <code>true</code> if beehive. <code>false</code> if not.
     */
    static bool isBeeHive(TileGID gid);

	/**
	 * Returns whether the given tile gid is of type flower.
	 * @param gid tile gid
	 * @return <code>true</code> if flower. <code>false</code> if not.
	 */
    static bool isFlower(TileGID gid);

	/**
	 * Returns the sprite corresponding to the given tile gid.
	 * @param gid gid of tile
	 * @return sprite of tile
	 */
	static cocos2d::Sprite *getSpriteOf(TileGID gid);

	/**
	 * Returns the seasonal tile of the given tile gid according to the season.
	 * @param gid tile gid
	 * @param season season to look up
	 * @return corresponding seasonal tile
	 */
	static TileGID getSeasonTileOf(TileGID gid, Season season);
};

#endif /* TILES_H */