
#ifndef PSE_BEE_GAME_HONEYMOVER_H
#define PSE_BEE_GAME_HONEYMOVER_H

#include <Game/TileMapLayer.h>
#include "cocos2d.h"

using namespace cocos2d;

/**
 * Moves a set amount of honey from beehive to a honey extractor or the other way
 */
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
