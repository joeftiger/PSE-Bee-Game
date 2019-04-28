//
// Created by julius on 14.04.19.
//

#ifndef PSE_BEE_GAME_PLACEABLESPRITE_H
#define PSE_BEE_GAME_PLACEABLESPRITE_H


#include <Resources/Sprites.h>
#include "Placeable.h"

class PlaceableSprite : public Placeable {
private:
	Sprites::SpriteID _id;

public:
	explicit PlaceableSprite(Sprites::SpriteID id);

	bool canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) override;

	void placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) override;

	Sprite *getSprite() override;
};

#endif //PSE_BEE_GAME_PLACEABLESPRITE_H
