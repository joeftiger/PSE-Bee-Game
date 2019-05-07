//
// Created by Uro on 3/30/2019.
//

#ifndef PSE_BEE_GAME_ITEMPANELLayer_H
#define PSE_BEE_GAME_ITEMPANELLayer_H

#include <Game/TileMapLayer.h>
#include <cocos/ui/UIButton.h>
#include "cocos2d.h"
#include "TouchUtil.h"

using namespace cocos2d;

class ItemPanelLayer : public LayerColor, public TouchUtil {
private:
    ui::Button *_showRec;
	bool _isItemShow;
	Point _touchPosition;
	TileMapLayer *_tileMapLayer;
	bool _isTouch;

public:
	static LayerColor *createLayer();

	virtual bool init();

	void initializeItemPanel();

	ui::Button *getShowRec();

	void setTileMap(TileMapLayer *tileMap);

	void showHideItemPanel();

	void touchOnItemPanel(const Vec2 &touchPos);

    bool onTouchBegan(Touch *touch, Event *event);

    void onTouchMoved(Touch *touch, Event *event);

    void onTouchEnded(Touch *touch, void *);

	CREATE_FUNC(ItemPanelLayer);
};


#endif //PSE_BEE_GAME_ITEMPANELLayer_H
