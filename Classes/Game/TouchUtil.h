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

    void setDrag(Point screenTouch, Point layerTouch);
    Sprite *getDrag();
    void addToSpriteList(string name, Vec2 pos, int tag, Size scale);
    bool isDrag();
    void addListTo(Layer *layer); //overloading
    void addListTo(Scene *scene);
};



#endif //PSE_BEE_GAME_DRAGDROP_H