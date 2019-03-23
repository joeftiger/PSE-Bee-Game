//
// Created by tb18a517 on 13.03.2019.
//

#ifndef __HUDLAYER_H
#define __HUDLAYER_H

#include "cocos2d.h"

using namespace cocos2d;

class HUDLayer: public cocos2d::Layer
{
private:

	unsigned int honey;
	Label *honeyLabel;

	float timePassed;
	Label *timeLabel;

public:
	static cocos2d::Layer *createLayer();
    virtual bool init();

	void timer(float dt);
    
    CREATE_FUNC(HUDLayer);
};


#endif //__HUDLAYER_H
