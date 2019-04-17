//
// Created by julius on 14.04.19.
//

#ifndef PSE_BEE_GAME_PLACEABLE_H
#define PSE_BEE_GAME_PLACEABLE_H

#include <Game/TileMapLayer.h>
#include <HeaderFiles/TileGID.h>
#include "cocos2d.h"

class TileMapLayer;

/**
 * A placeable object is handled by the TileMapLayer to place tile/trees/houses etc.
 */
class Placeable {
public:
    /**
     * Returns the size of this placeable object (in tiles).
     * Needed to check for obstructions
     * @return size in tiles
     */
    virtual cocos2d::Size size() = 0;

    /**
     * Returns the center of this placeable object (in tiles).
     * Needed to precisely place the
     * @return center position
     */
    virtual cocos2d::Vec2 center() = 0;

    virtual bool canPlaceOn(TileMapLayer &tileMapLayer, cocos2d::Vec2 &position) = 0;

    virtual void placeOn(TileMapLayer &tileMapLayer, cocos2d::Vec2 &position) = 0;
};
#endif //PSE_BEE_GAME_PLACEABLE_H
