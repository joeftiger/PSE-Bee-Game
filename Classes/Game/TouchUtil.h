//
// Created by Uro on 3/29/2019.
//

#ifndef PSE_BEE_GAME_DRAGDROP_H
#define PSE_BEE_GAME_DRAGDROP_H

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;


class TouchUtil {
protected:
    bool _isDrag = false;
    Sprite *drag;
    vector<Sprite*> spriteList;
public:

    Sprite *getDrag(Point touch);
    void addToSpriteList(string name, Vec2 pos, int tag);
    bool isDrag();
    void addListTo(Scene *scene);
};


#endif //PSE_BEE_GAME_DRAGDROP_H
