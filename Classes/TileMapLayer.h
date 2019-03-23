//
// Created by julius on 21.03.19.
//

#ifndef PSE_BEE_GAME_TILEMAPLAYER_H
#define PSE_BEE_GAME_TILEMAPLAYER_H

#include "cocos2d.h"

USING_NS_CC;

class TileMapLayer : public cocos2d::Layer {
private:
    TMXTiledMap *_tileMap;

public:
    virtual bool init();

    ssize_t getTreeCount();
    ssize_t getFlowerCount();
    std::vector<cocos2d::Sprite*> getBeeHives();

    // implement the "static create()" method manually
    CREATE_FUNC(TileMapLayer);
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H
