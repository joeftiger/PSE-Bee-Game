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

public:
    /**
     * Creates the beehive popup with given beehive to extract information from.
     * @param beeHive beehive to display
     * @return Node
     */
    static BeeHivePopup *createWith(BeeHive *beeHive);

    bool init() override;

    // implement the "static create()" method manually
    CREATE_FUNC(BeeHivePopup);
};


#endif //PSE_BEE_GAME_BEEHIVEPOPUP_H
