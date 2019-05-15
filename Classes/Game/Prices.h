#ifndef PRICES_H
#define PRICES_H

#include "Resources/Sprites.h"
#include "Resources/Tiles.h"

class Prices {
private:
public:

	static int getPriceForSprite(Sprites::SpriteID id);

	static int getPriceForTile(Tiles::TileGID id);

};


#endif // !PRICES_H



