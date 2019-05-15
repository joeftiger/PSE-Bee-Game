
#ifndef PLACEABLE_H
#define PLACEABLE_H

#include "../Game/TileMapLayer.h"
#include "../Resources/Tiles.h"
#include "cocos2d.h"

class TileMapLayer;

/**
 * A placeable object is handled by the TileMapLayer to place tile/trees etc.
 */
class Placeable {
public:
	virtual bool canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) = 0;

	virtual void placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) = 0;

	virtual cocos2d::Sprite *getSprite() = 0;
	
	virtual int getPrice() = 0;
};

#endif //PLACEABLE_H
