

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene: public cocos2d::Scene
{
private:
    TMXTiledMap *_tileMap;
    TMXLayer *_background;

    Sprite *_player;
public:
    static cocos2d::Scene* createScene();

    void onTouchEnded(Touch *touch,Event *unused_event);
    void setPlayerPosition(Point position);

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
