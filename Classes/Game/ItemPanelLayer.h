//
// Created by Uro on 3/30/2019.
//

#ifndef PSE_BEE_GAME_ITEMPANELLayer_H
#define PSE_BEE_GAME_ITEMPANELLayer_H

#include "cocos2d.h"
#include "TouchUtil.h"

using namespace cocos2d;

class ItemPanelLayer : public LayerColor, public TouchUtil {
private:
	LayerColor *_showRec;
	bool _isItemShow;

public:
	static LayerColor *createLayer();

	virtual bool init();

	void initializeItemPanel();

	LayerColor *getShowRec();

	void showHideItemPanel(Point touchPos);

	void touchOnItemPanel(Point touchPos);

	CREATE_FUNC(ItemPanelLayer);
};


#endif //PSE_BEE_GAME_ITEMPANELLayer_H
