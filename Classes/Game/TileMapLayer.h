//
// Created by julius on 21.03.19.
//

#ifndef PSE_BEE_GAME_TILEMAPLAYER_H
#define PSE_BEE_GAME_TILEMAPLAYER_H

#include "cocos2d.h"
#include "Observable.h"
#include "HeaderFiles/TileGID.h"

USING_NS_CC;

class TileMapLayer : public cocos2d::Layer, public Observable {
private:
    TMXTiledMap *_tileMap;

public:
    virtual bool init() override;

    ssize_t getTreeCount();
    ssize_t getFlowerCount();
    std::vector<cocos2d::Sprite*> getBeeHives();
	TMXTiledMap *getMap();

	Vec2 getTilePosition(Vec2 pos);
	Vec2 inTileMapBounds(Vec2 pos);
	void setTile(Vec2 position, TileGID gid);


    // implement the "static create()" method manually
    CREATE_FUNC(TileMapLayer)
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H