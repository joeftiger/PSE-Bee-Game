//
// Created by julius on 21.03.19.
//

#ifndef PSE_BEE_GAME_TILEMAPLAYER_H
#define PSE_BEE_GAME_TILEMAPLAYER_H

#include "cocos2d.h"
#include "Observable.h"

USING_NS_CC;

class TileMapLayer : public cocos2d::Layer, public Observable {
private:
    TMXTiledMap *_tileMap;

    std::vector<Observer*> _observers;

public:
    virtual bool init();

    ssize_t getTreeCount();
    ssize_t getFlowerCount();
    std::vector<cocos2d::Sprite*> getBeeHives();
	TMXTiledMap *getMap();

	void observe(Observer* observer) override;

    // implement the "static create()" method manually
    CREATE_FUNC(TileMapLayer);
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H
