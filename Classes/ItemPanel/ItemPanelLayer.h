
#ifndef ITEMPANELLayer_H
#define ITEMPANELLayer_H

#include <Game/TileMapLayer.h>
#include <cocos/ui/UIButton.h>
#include "cocos2d.h"
#include "TouchUtil.h"

using namespace cocos2d;

/**
 * ItemPanelLayer that holds sprites and tiles to be set on the tileMap
 */
class ItemPanelLayer : public LayerColor, public TouchUtil {
private:
	bool _isItemShow;
	TileMapLayer *_tileMapLayer;
	bool _isTouch;

public:
	static LayerColor *createLayer();

	virtual bool init();

	/**
	 * Initializes the sprites that can be dragged and placed.
	 */
	void initializeItemPanel();

	void setTileMap(TileMapLayer *tileMap);

	/**
	 * show / hide the item panel
	 */
	void showHideItemPanel();

	void touchOnItemPanel(const Vec2 &touchPos);

    bool onTouchBegan(Touch *touch, Event *event);

    void onTouchMoved(Touch *touch, Event *event);

    void onTouchEnded(Touch *touch, void *);

	CREATE_FUNC(ItemPanelLayer);
};


#endif //ITEMPANELLayer_H
