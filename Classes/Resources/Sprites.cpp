//
// Created by julius on 28.04.19.
//

#include "Sprites.h"
#include "SpriteContainer.h"

cocos2d::Sprite *Sprites::getSpriteOf(Sprites::SpriteID &gid) {
    return SpriteContainer::getInstance()->getSpriteOf(gid);
}
