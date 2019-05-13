
#ifndef HONEYEXTRACTORPOPUP_H
#define HONEYEXTRACTORPOPUP_H

#include "cocos2d.h"
#include <Game/HoneyExtractor.h>

using namespace cocos2d;

class HoneyExtractorPopup : public Node {
private:
	HoneyExtractor *_honeyExtractor;

	Label * _honeyLabel;

	Sprite * _background;

    /**
     * Initializes the background image.
     */
	void initBackground();

    /**
     * Initializes the honeyExtractor image shown.
     */
	void initImage();

    /**
     * Initializes the information panel of the honeyExtractor.
     */
	void initInfoPanel();

    /**
     * Initializes the interaction buttons.
     */
	void initButtons();

    /**
     * Initializes the touches on this layer.
     */
	void initTouch();

    /**
     * update Labels.
     */
	void update(float dt) override;

public:
    /**
     * Creates the honeyExtractor popup with given honeyExtractor to get information from.
     * @param honeyExtractor honeyExtractor to display
     * @return Node
     */
	static HoneyExtractorPopup* createWith(HoneyExtractor *honeyExtractor);

	bool init() override;

	bool onTouchBegan(Touch *touch, Event *event);

	CREATE_FUNC(HoneyExtractorPopup);

};

#endif //HONEYEXTRACTORPOPUP_H