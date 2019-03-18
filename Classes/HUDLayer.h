//
// Created by tb18a517 on 13.03.2019.
//

#ifndef __HUDLAYER_H
#define __HUDLAYER_H

#include "cocos2d.h"



class HUDLayer: public cocos2d::Layer
{


public:
	HUDLayer();

    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(HUDLayer);
};


#endif //__HUDLAYER_H
