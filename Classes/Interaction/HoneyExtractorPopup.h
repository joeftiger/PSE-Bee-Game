
#ifndef HONEYEXTRACTORPOPUP_H
#define HONEYEXTRACTORPOPUP_H

#include "cocos2d.h"
#include <Game/HoneyExtractor.h>

using namespace cocos2d;

class HoneyExtractorPopup : public Node {
private:
	HoneyExtractor *_honeyExtractor;

	void initBackground();

	void initImage();

	void initInfoPanel();

	void initButtons();

	void initTouch();

	void update(float dt);

public:
	
	static HoneyExtractorPopup* createWith(HoneyExtractor *honeyExtractor);

	bool init() override;

	bool onTouchBegan(Touch *touch, Event *event);

	CREATE_FUNC(HoneyExtractorPopup);

};

#endif //HONEYEXTRACTORPOPUP_H