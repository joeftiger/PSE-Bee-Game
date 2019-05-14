
#ifndef HONEYMOVER_H
#define HONEYMOVER_H

#include <Game/TileMapLayer.h>
#include "cocos2d.h"

using namespace cocos2d;

/**
 * Moves a set amount of honey from beehive to a honey extractor, and interacts with them.
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

    /**
     * Looks if a touch happens on a @BeeHive or @HoneyExtractor, if it's the case
     * it either pops up a bee hive or extractor to interact with.
     */
    bool onTouchBegan(Touch *touch, Event *event);

    /**
     * If the touch is moved it drags the honey.
     */
    void onTouchMoved(Touch *touch, Event *event);

    void onTouchEnded(Touch *touch, void *);

    void interactAt(const Vec2& pos);


    CREATE_FUNC(HoneyMover);
};


#endif //HONEYMOVER_H
