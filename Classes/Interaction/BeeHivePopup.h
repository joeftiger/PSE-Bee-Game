
#ifndef BEEHIVEPOPUP_H
#define BEEHIVEPOPUP_H

#include <Game/BeeHive.h>
#include "cocos2d.h"

USING_NS_CC;
/**
 * Pop-up window with information for beehives (honey, varroa, population)
 */
class BeeHivePopup : public Node {
private:
    BeeHive *_beeHive;
    Label * _honeyLabel;
    Label * _beesLabel;
    Label * _varroaLabel;
    Label * _foodLabel;
	Sprite *_background;

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
    void update(float dt) override;

    /**
     * For better readability of labels.
     */
     std::string stringShortener(std::string s);

public:
    /**
     * Creates the beehive popup with given beehive to get information from.
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


#endif //BEEHIVEPOPUP_H
