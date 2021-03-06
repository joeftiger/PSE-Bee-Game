#ifndef PRICES_H
#define PRICES_H

#include "Resources/Sprites.h"
#include "Resources/Tiles.h"

/**
*	Responsible for holding Pricing-Information about Placeables
*/
class Prices {
private:
public:

	static int getPriceForSprite(Sprites::SpriteID id);

	static int getPriceForTile(Tiles::TileGID id);

	static int getPriceForMedicine();

	static int getPriceForSugarWater();

	static int getPriceForSprite();

	static int getPriceForRevive();

};


#endif // !PRICES_H



