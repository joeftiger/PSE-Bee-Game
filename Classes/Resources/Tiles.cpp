
#include "Tiles.h"
#include "SpriteContainer.h"


bool Tiles::isBeeHive(Tiles::TileGID gid) {
	return  gid == beehive_small  || gid == beehive_small_open  || gid == beehive_small_winter  ||
			gid == beehive_middle || gid == beehive_middle_open || gid == beehive_middle_winter || gid == beehive_middle_overflow ||
			gid == beehive_big    || gid == beehive_big_open    || gid == beehive_big_winter    || gid == beehive_big_overflow;
}

bool Tiles::isFlower(Tiles::TileGID gid) {
	return gid == Tiles::flower_blue_big || gid == Tiles::flower_blue_middle || gid == Tiles::flower_blue_small ||
	       gid == Tiles::flower_pink_big || gid == Tiles::flower_pink_middle || gid == Tiles::flower_pink_small ||
	       gid == Tiles::flower_red_big  || gid == Tiles::flower_red_middle  || gid == Tiles::flower_red_small  ||
	       gid == Tiles::flower_white_big|| gid == Tiles::flower_white_middle|| gid == Tiles::flower_white_small;
}

cocos2d::Sprite *Tiles::getSpriteOf(Tiles::TileGID gid) {
    return SpriteContainer::getInstance()->getSpriteOf(gid);
}

Tiles::TileGID Tiles::getSeasonTileGIDof(Tiles::TileGID gid, Season season) {
	switch (gid) {
		case beehive_small:
		case beehive_middle:
		case beehive_big:
		case brushwood_small:
		case bush_small:
		case bush_big:
		case brushwood_big:
			return season == Season::Winter ? (TileGID) (gid + 10) : gid;

		case grass:
		case snow:
			return season == Season::Winter ? snow : grass;

		case beehive_small_winter:
		case beehive_middle_winter:
		case beehive_big_winter:
		case brushwood_small_winter:
		case bush_small_winter:
		case bush_big_winter:
		case brushwood_big_winter:
			return season == Season::Winter ? gid : (TileGID) (gid - 10);

		case flower_blue_small:
		case flower_blue_middle:
		case flower_blue_big:
		case snow_1:
			if (season == Season::Spring) return flower_blue_big;
			if (season == Season::Summer) return flower_blue_middle;
			if (season == Season::Fall)   return flower_blue_small;
			return snow_1;

		case flower_red_small:
		case flower_red_middle:
		case flower_red_big:
		case snow_2:
			if (season == Season::Spring) return flower_red_big;
			if (season == Season::Summer) return flower_red_middle;
			if (season == Season::Fall)   return flower_red_small;
			return snow_2;

		case flower_white_small:
		case flower_white_middle:
		case flower_white_big:
		case snow_3:
			if (season == Season::Spring) return flower_white_big;
			if (season == Season::Summer) return flower_white_middle;
			if (season == Season::Fall)   return flower_white_small;
			return snow_3;

		case flower_pink_small:
		case flower_pink_middle:
		case flower_pink_big:
		case snow_4:
			if (season == Season::Spring) return flower_pink_big;
			if (season == Season::Summer) return flower_pink_middle;
			if (season == Season::Fall)   return flower_pink_small;
			return snow_4;

		default:
			return gid;
	}
}
