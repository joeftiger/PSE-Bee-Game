//
// Created by julius on 14.04.19.
//

#ifndef PSE_BEE_GAME_TILEGID_H
#define PSE_BEE_GAME_TILEGID_H


#include <TileMapObjects/Placeable.h>

/**
 * A tile is a placeable object
 */
class TileGID : public Placeable {
public:
    enum {
        beehiveBig = 1,
        beehiveSmall = 2,
        beehiveMiddle = 3,
        flower1 = 11,
        flower2 = 12,
        flower3 = 13,
        flower4 = 14,
        bush1 = 5,
        bush2 = 10,
        bush3 = 15,
        bush4 = 16,
        grass = 17,
        road = 18,
        obstruction = 19,
        no_obstruction = 20
    };

    cocos2d::Size size() override;

    cocos2d::Vec2 center() override;
};


#endif //PSE_BEE_GAME_TILEGID_H
