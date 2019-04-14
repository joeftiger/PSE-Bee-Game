//
// Created by julius on 14.04.19.
//

#ifndef PSE_BEE_GAME_PLACEABLE_H
#define PSE_BEE_GAME_PLACEABLE_H

#include "cocos2d.h"

class Placeable {
public:
    /**
     * Returns the size of this placeable object (in tiles).
     * @return size in tiles
     */
    virtual cocos2d::Size size() = 0;

    /**
     * Returns the center of this placeable object (in tiles).
     * @return center position
     */
    virtual cocos2d::Vec2 center() = 0;
};
#endif //PSE_BEE_GAME_PLACEABLE_H
