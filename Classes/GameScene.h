

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "MainMenuScene.h"
#include "cocos2d.h"


using namespace cocos2d;

class GameScene: public cocos2d::Scene
{
private:
    TMXTiledMap *_tileMap;
    TMXLayer *_background;
    Sprite *_player;

    bool _isTouched;
    Touch *_touch;
    Point _touchPosition;
public:
    static cocos2d::Scene* createScene();

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(void *, void *);

    void setPlayerPosition(Point position);

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
