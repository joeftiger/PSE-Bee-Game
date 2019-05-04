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
