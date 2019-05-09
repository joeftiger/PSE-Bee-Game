//
// Created by julius on 28.04.19.
//

#include "Sprites.h"
#include "SpriteContainer.h"

bool Sprites::isHoneyExtractor(Sprites::SpriteID id) {
	return id == Sprites::honey_extractor;
}


cocos2d::Sprite *Sprites::getSpriteOf(Sprites::SpriteID gid) {
    return SpriteContainer::getInstance()->getSpriteOf(gid);
}

Sprites::SpriteID Sprites::getSeasonSpriteIDof(Sprites::SpriteID id, Season season) {
	switch (id) {
		case tree_1_spring_summer:
		case tree_1_fall:
		case tree_1_winter:
		case tree_1_apple_1:
		case tree_1_apple_2:
		case tree_1_apple_3:
			if (season == Season::Fall)     return tree_1_fall;
			if (season == Season::Winter)   return tree_1_winter;
			else                            return tree_1_spring_summer;

		case tree_2_spring_summer:
		case tree_2_fall:
		case tree_2_winter:
		case tree_2_apple_1:
		case tree_2_apple_2:
		case tree_2_apple_3:
			if (season == Season::Fall)     return tree_2_fall;
			if (season == Season::Winter)   return tree_2_winter;
			else                            return tree_2_spring_summer;

		case tree_3_spring_summer_fall:
		case tree_3_winter:
			if (season == Season::Winter)   return tree_3_winter;
			else                            return tree_3_spring_summer_fall;

		case tree_4_spring_summer:
		case tree_4_fall:
		case tree_4_winter:
		case tree_4_apple_1:
		case tree_4_apple_2:
		case tree_4_apple_3:
			if (season == Season::Fall)     return tree_4_fall;
			if (season == Season::Winter)   return tree_4_winter;
			else                            return tree_4_spring_summer;

		default:
			return id;
	}
}
