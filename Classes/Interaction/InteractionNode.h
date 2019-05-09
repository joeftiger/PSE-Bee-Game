
#ifndef PSE_BEE_GAME_INTERACTIONNODE_H
#define PSE_BEE_GAME_INTERACTIONNODE_H

#include "cocos2d.h"

using namespace cocos2d;

/**
 * Interaction functionality as a node to be used in other objects / classes
 */
class InteractionNode : public Node {
private:
    std::string _itemName;
    Sprite *_background;
    Sprite *_item;

public:

    static Node *createNode();
    virtual bool init();

    /**
     * initialization of the item (e.g. BeeHive) to interact with.
     * @param name
     */
    void setFiles(std::string itemName);

    void runAnimation();

	void setUpTouches();

    CREATE_FUNC(InteractionNode);
};


#endif //PSE_BEE_GAME_INTERACTIONNODE_H
