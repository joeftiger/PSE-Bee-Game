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

    /**
     * Returns the positions of each beehive on the tile map.
     * @return a list of beehive-positions
     */
    std::vector<Vec2> getBeeHives();

	TMXTiledMap *getMap();

	Vec2 getTilePosition(Vec2 pos);
	Vec2 inTileMapBounds(Vec2 pos);
	void setTile(Vec2 position, int gid);


    // implement the "static create()" method manually
    CREATE_FUNC(TileMapLayer)
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H
