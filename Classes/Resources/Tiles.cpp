//
// Created by julius on 28.04.19.
//

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

Tiles::TileGID Tiles::getSeasonTileOf(Tiles::TileGID gid, Season season) {
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
			return season == Season::Winter ? snow_1 : Season::Spring ? flower_blue_big : Season::Summer ? flower_blue_middle : flower_blue_small;

		case flower_red_small:
		case flower_red_middle:
		case flower_red_big:
			return season == Season::Winter ? snow_2 : Season::Spring ? flower_red_big : Season::Summer ? flower_red_middle : flower_red_small;

		case snow:
			return season == Season::Winter ? snow : grass;

		case flower_white_small:
		case flower_white_middle:
		case flower_white_big:
			return season == Season::Winter ? snow_3 : Season::Spring ? flower_white_big : Season::Summer ? flower_white_middle : flower_white_small;

		case flower_pink_small:
		case flower_pink_middle:
		case flower_pink_big:
			return season == Season::Winter ? snow_4 : Season::Spring ? flower_pink_big : Season::Summer ? flower_pink_middle : flower_pink_small;

		case snow_1:
			return season == Season::Winter ? snow_1 : Season::Spring ? flower_blue_big : Season::Summer ? flower_blue_middle : flower_blue_small;

		case snow_2:
			return season == Season::Winter ? snow_2 : Season::Spring ? flower_red_big : Season::Summer ? flower_red_middle : flower_red_small;

		case snow_3:
			return season == Season::Winter ? snow_3 : Season::Spring ? flower_white_big : Season::Summer ? flower_white_middle : flower_white_small;

		case snow_4:
			return season == Season::Winter ? snow_4 : Season::Spring ? flower_pink_big : Season::Summer ? flower_pink_middle : flower_pink_small;

		default:
			return gid;
	}
}
