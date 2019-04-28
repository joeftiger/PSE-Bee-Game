//
// Created by julius on 28.04.19.
//

#include <Game/TileMapLayer.h>
#include "HeaderFiles/DEFINITIONS.h"
#include "Tiles.h"

void Tiles::addSprites() {
    const std::string path = "tilemaps/Tiles/";
    _tileSprites.emplace(beehiveBig1    , cocos2d::Sprite::create(path + "bienenstock1_gross.png"));
    _tileSprites.emplace(beehiveSmall1  , cocos2d::Sprite::create(path + "bienenstock1_klein.png"));
    _tileSprites.emplace(beehiveMiddle1 , cocos2d::Sprite::create(path + "bienenstock1_mittel.png"));
    _tileSprites.emplace(beehiveBig2    , cocos2d::Sprite::create(path + "bienenstock2_gross.png"));
    _tileSprites.emplace(beehiveSmall2  , cocos2d::Sprite::create(path + "bienenstock2_klein.png"));
    _tileSprites.emplace(beehiveMiddle2 , cocos2d::Sprite::create(path + "bienenstock2_mittel.png"));
    _tileSprites.emplace(beehiveBig3    , cocos2d::Sprite::create(path + "bienenstock3_gross.png"));
    _tileSprites.emplace(beehiveMiddle3 , cocos2d::Sprite::create(path + "bienenstock3_mittel.png"));
    _tileSprites.emplace(flower1        , cocos2d::Sprite::create(path + "blumen1_spring_summmer.png"));
    _tileSprites.emplace(flower2        , cocos2d::Sprite::create(path + "blumen2_spring_summmer.png"));
    _tileSprites.emplace(flower3        , cocos2d::Sprite::create(path + "blumen3_spring_summmer.png"));
    _tileSprites.emplace(flower4        , cocos2d::Sprite::create(path + "blumen4_spring_summmer.png"));
    _tileSprites.emplace(bush1          , cocos2d::Sprite::create(path + "busch1_spring_summmer.png"));
    _tileSprites.emplace(bush2          , cocos2d::Sprite::create(path + "busch2_spring_summmer.png"));
    _tileSprites.emplace(bush3          , cocos2d::Sprite::create(path + "busch3_spring_summmer.png"));
    _tileSprites.emplace(bush4          , cocos2d::Sprite::create(path + "busch4_spring_summmer.png"));
    _tileSprites.emplace(grass          , cocos2d::Sprite::create(path + "grasflàche.png"));
    _tileSprites.emplace(road           , cocos2d::Sprite::create(path + "steinplattenboden.png"));

    // these are currently only in the spritesheetSD.png
    _tileSprites.emplace(obstruction    , nullptr);
    _tileSprites.emplace(no_obstruction , nullptr);
}

cocos2d::Sprite *Tiles::getSpriteOf(Tiles::TileGID &gid) {
    if (_tileSprites.empty()) {
        addSprites();
    }
    return _tileSprites[gid];
}
