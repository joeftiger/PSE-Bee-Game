//
// Created by uro on 5/1/19.
//

#ifndef PSE_BEE_GAME_HONEYMOVER_H
#define PSE_BEE_GAME_HONEYMOVER_H

#include <Game/TileMapLayer.h>
#include "cocos2d.h"

using namespace cocos2d;

class HoneyMover : public Node {
private:
    TileMapLayer *_tileMapLayer;
    BeeHive* _beeHive;
    HoneyExtractor* _extractor;
    Sprite * _honeySprite;
    bool _isDrag = false;
public:

    static Node *createNode();
    virtual bool init();

    void setTileMap(TileMapLayer* tileMap);

    bool onTouchBegan(Touch *touch, Event *event);

    void onTouchMoved(Touch *touch, Event *event);

    void onTouchEnded(Touch *touch, void *);

    void interactAt(const Vec2& pos);


    CREATE_FUNC(HoneyMover);
};


#endif //PSE_BEE_GAME_HONEYMOVER_H
