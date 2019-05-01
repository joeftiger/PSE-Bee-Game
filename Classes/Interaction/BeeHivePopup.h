//
// Created by julius on 30.04.19.
//

#ifndef PSE_BEE_GAME_BEEHIVEPOPUP_H
#define PSE_BEE_GAME_BEEHIVEPOPUP_H

#include <Game/BeeHive.h>
#include "cocos2d.h"

USING_NS_CC;

class BeeHivePopup : public Node {
private:
    BeeHive *_beeHive;
    Label * _honeyLabel;
    Label * _beesLabel;
    Label * _varroaLabel;

    /**
     * Initializes the background image.
     */
    void initBackground();

    /**
     * Initializes the beehive image shown.
     */
    void initImage();

    /**
     * Initializes the information panel of the beehive.
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
    void update(float dt);

    /**
     * For better readability of labels.
     */
     std::string stringShortener(std::string s);

public:
    /**
     * Creates the beehive popup with given beehive to extract information from.
     * @param beeHive beehive to display
     * @return Node
     */
    static BeeHivePopup *createWith(BeeHive *beeHive);

    bool init() override;

    bool onTouchBegan(Touch *touch, Event *event);

    /**
     * Lable for pop up, honey, bees, varroa.
     * @param string
     */

    // implement the "static create()" method manually
    CREATE_FUNC(BeeHivePopup);
};


#endif //PSE_BEE_GAME_BEEHIVEPOPUP_H
