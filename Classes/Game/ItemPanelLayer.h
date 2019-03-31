//
// Created by Uro on 3/30/2019.
//

#ifndef PSE_BEE_GAME_ITEMPANELLayer_H
#define PSE_BEE_GAME_ITEMPANELLayer_H

#include "cocos2d.h"
#include "TouchUtil.h"

using namespace cocos2d;

class ItemPanelLayer: public LayerColor{
    private:
        LayerColor *_showRec;

    public:
        static LayerColor *createLayer();
        virtual bool init();

        void initializeItemPanel(TouchUtil *parent);
        LayerColor* getShowRec();

        CREATE_FUNC(ItemPanelLayer);
};


#endif //PSE_BEE_GAME_ITEMPANELLayer_H
