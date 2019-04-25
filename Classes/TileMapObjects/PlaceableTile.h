//
// Created by julius on 14.04.19.
//

#ifndef PSE_BEE_GAME_PLACEABLETILE_H
#define PSE_BEE_GAME_PLACEABLETILE_H


#include <TileMapObjects/Placeable.h>

/**
 * A tile is a placeable object for the tilemap of the TileMapLayer.
 */
class PlaceableTile : public Placeable {
private:
	TileGID _gid;
public:

	explicit PlaceableTile(TileGID gid);

	bool canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) override;

	void placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) override;
};


#endif //PSE_BEE_GAME_PLACEABLETILE_H