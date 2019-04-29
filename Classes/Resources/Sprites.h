//
// Created by julius on 28.04.19.
//

#ifndef PSE_BEE_GAME_SPRITES_H
#define PSE_BEE_GAME_SPRITES_H


#include <cocos/2d/CCSprite.h>

class Sprites {
public:
    enum SpriteID {
        tree_1,
        tree_1_apple_1,
        tree_1_apple_2,
        tree_1_apple_3,
        tree_2,
        tree_2_apple_1,
        tree_2_apple_2,
        tree_2_apple_3,
        tree_3_summer,
        tree_3_winter,
        tree_4,
        tree_4_apple_1,
        tree_4_apple_2,
        tree_4_apple_3,
        erlenmeyer,
        honey_glass_2d,
        honey_glass_3d,
        honey_bucket,
        honey_extractor,
        coin_single,
        coin_pile
    };

    /**
	 * Returns the sprite corresponding to the given sprite id.
	 * @param id id of sprite
	 * @return sprite
	 */
    static cocos2d::Sprite *getSpriteOf(SpriteID id);
};


#endif //PSE_BEE_GAME_SPRITES_H