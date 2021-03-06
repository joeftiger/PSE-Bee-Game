
#ifndef SPRITECONTAINER_H
#define SPRITECONTAINER_H

#include "cocos2d.h"
#include "Sprites.h"
#include "Tiles.h"

USING_NS_CC;

/**
 * converting sprites and tiles to their corresponding images for further use
 */
class SpriteContainer {
private:
    SpriteFrameCache *_cache = SpriteFrameCache::getInstance();

    SpriteContainer();

    /**
     * Loads the spritesheet.
     */
    void loadSpriteSheet();

public:
    static SpriteContainer *getInstance() {
        static auto instance = new SpriteContainer();
        return instance;
    }

    /**
	 * Returns the sprite corresponding to the given tile gid.
	 * @param gid gid of tile
	 * @return sprite of tile
	 */
    Sprite *getSpriteOf(Tiles::TileGID gid);

    /**
	 * Returns the sprite corresponding to the given sprite id.
	 * @param id id of sprite
	 * @return sprite
	 */
    Sprite *getSpriteOf(Sprites::SpriteID id);

    /**
     * Returns the sprite frame name of the given sprite id.
     * @param id sprite id
     * @return corresponding sprite frame name
     */
    std::string getSpriteFrameNameOf(Sprites::SpriteID id);

	/**
	 * Returns the sprite frame of the given sprite id.
	 * @param id sprite id
	 * @return corresponding sprite frame
	 */
    SpriteFrame *getSpriteFrameOf(Sprites::SpriteID id);
};


#endif //SPRITECONTAINER_H
