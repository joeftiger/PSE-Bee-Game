#include "Prices.h"

int Prices::getPriceForSprite(Sprites::SpriteID id) {
	if (Sprites::isTree(id)) {
		return 400;
	}
	else {
		switch (id) {
		default: return 200; //Add more sprites if needed
		}
	}
}

int Prices::getPriceForTile(Tiles::TileGID id) {
	if (Tiles::isBeeHive(id)) {
		return 200;
	}
	else if(Tiles::isFlower(id)){
		return 50;
	}
	else {
		switch (id) {
		case Tiles::grass:
		case Tiles::road:  return 50;

		case Tiles::bush_small:
		case Tiles::bush_big: return 100;

		case Tiles::honeyextractor_summer: return 400;

		default: return 50;
		}
	}
}

int Prices::getPriceForMedicine() {
	return 200;
}

int Prices::getPriceForSugarWater() {
	return 100;
}

int Prices::getPriceForRevive() {
	return 300;
}