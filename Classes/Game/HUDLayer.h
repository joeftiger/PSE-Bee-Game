
#ifndef __HUDLAYER_H
#define __HUDLAYER_H

#include "cocos2d.h"

using namespace cocos2d;

class HUDLayer : public Layer {
private:

	unsigned int honey;
	Label *honeyLabel;

	float timePassed;
	Label *timeLabel;

	float money;
	Label *moneyLabel;

	float onePofScreenH;
	float onePofScreenW;

	int years;
	int months;

public:
	static cocos2d::Layer *createLayer();

	virtual bool init();

	void timer(float dt);

	std::string stringShortener(std::string s);

	CREATE_FUNC(HUDLayer);
};


#endif //__HUDLAYER_H
