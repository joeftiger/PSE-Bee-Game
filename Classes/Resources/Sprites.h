
#ifndef SPRITES_H
#define SPRITES_H


#include <cocos/2d/CCSprite.h>
#include <HeaderFiles/Seasons.h>

/**
 * list of all of the IDs of sprites as well as testing if they correspond to certain objects
 */
class Sprites {
public:
    enum SpriteID : int {
        tree_1_spring_summer,
        tree_1_fall,
        tree_1_winter,
        tree_1_apple_1,
        tree_1_apple_2,
        tree_1_apple_3,
        tree_2_spring_summer,
        tree_2_fall,
        tree_2_winter,
        tree_2_apple_1,
        tree_2_apple_2,
        tree_2_apple_3,
        tree_3_spring_summer_fall,
        tree_3_winter,
        tree_4_spring_summer,
        tree_4_fall,
        tree_4_winter,
        tree_4_apple_1,
        tree_4_apple_2,
        tree_4_apple_3,
        start,
        options,
        credits,
        exit,
        shop_1,
        shop_2,
        shop_bg,
        minus,
        plus,
        erlenmeyer,
        honey_glass_2d,
        honey_glass_3d,
        honey_bucket,
        honey_extractor,
        coin_single,
        coin_pile
    };

    /**
	 * Returns whether the given sprite id is of type honey extractor.
	 * @param id sprite id
	 * @return <code>true</code> if honey extractor. <code>false</code> if not.
	 */
    static bool isHoneyExtractor(SpriteID id);

    /**
     * Returns whether the given sprite is is of type tree.
     * @param id sprite id
     * @return <code>true</code> if tree. <code>false</code> if not.
     */
    static bool isTree(SpriteID id);

    /**
	 * Returns the sprite corresponding to the given sprite id.
	 * @param id id of sprite
	 * @return sprite
	 */
    static cocos2d::Sprite *getSpriteOf(SpriteID id);

    /**
	 * Returns the seasonal sprite id of the given sprite id according to the season.
     * If not a tree, the sprite id itself will be returned.
     * The seasonal sprites contain no apples.
     *
	 * @param id sprite gid
	 * @param season season to look up
	 * @return corresponding seasonal sprite id
	 */
    static Sprites::SpriteID getSeasonSpriteIDof(SpriteID id, Season season);

	static int getPriceOfSprite(Sprites::SpriteID id);
};


#endif //SPRITES_H
