//
// Created by julius on 28.04.19.
//

#include "Tiles.h"
#include "SpriteContainer.h"

cocos2d::Sprite *Tiles::getSpriteOf(Tiles::TileGID &gid) {
    return SpriteContainer::getInstance()->getSpriteOf(gid);
}
