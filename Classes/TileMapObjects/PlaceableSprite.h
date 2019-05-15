
#ifndef PLACEABLESPRITE_H
#define PLACEABLESPRITE_H


#include "../Resources/Sprites.h"
#include "Placeable.h"

class PlaceableSprite : public Placeable {
private:
	Sprites::SpriteID _id;
	Size _size;

public:
	explicit PlaceableSprite(Sprites::SpriteID id);

	const Size &getSize() const;

	bool canPlaceOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) override;

	void placeOn(TileMapLayer *tileMapLayer, cocos2d::Vec2 &position) override;

	Sprite *getSprite() override;
};

#endif //PLACEABLESPRITE_H
