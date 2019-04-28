//
// Created by uro on 4/28/19.
//

#ifndef PSE_BEE_GAME_INTERACTIONNODE_H
#define PSE_BEE_GAME_INTERACTIONNODE_H

#include "cocos2d.h"

using namespace cocos2d;

class InteractionNode : public Node {
private:

public:
    static Node *createNode();
    virtual bool init();

    /**
     * initialization of the item (e.g. BeeHive) to interact with.
     * @param name
     */
    void initializeInteractionItem(std::string name);

    CREATE_FUNC(InteractionNode);
};


#endif //PSE_BEE_GAME_INTERACTIONNODE_H
