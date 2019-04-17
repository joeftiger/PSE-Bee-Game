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
	virtual bool canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) = 0;

	virtual void placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) = 0;
};

#endif //PSE_BEE_GAME_PLACEABLE_H
